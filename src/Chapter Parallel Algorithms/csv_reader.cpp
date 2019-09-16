#include <algorithm>
#include <charconv>
#include <chrono>
#include <execution>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <string>

class ScopeTimer
{
public:
	ScopeTimer(std::string name) : mName(std::move(name)), mStart(std::chrono::steady_clock::now()) { }
	~ScopeTimer() 
	{ 
		const auto end = std::chrono::steady_clock::now();
		std::cout << mName << ": " << std::chrono::duration <double, std::milli>(end - mStart).count() << " ms\n";
	}

private:
	const std::string mName;
	const std::chrono::time_point<std::chrono::steady_clock> mStart;
};

std::optional<std::string> GetFileContents(const std::filesystem::path& filename)
{
	ScopeTimer _t(__func__);
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);
	if (inFile)
	{
		inFile.seekg(0, std::ios::end);
		const auto filePos = inFile.tellg();
		if (filePos > 0)
		{
			std::string str(static_cast<size_t>(filePos), 0);

			inFile.seekg(0, std::ios::beg);
			inFile.read(str.data(), str.size());
			if (inFile)
				return str;
			else
				std::cerr << "Could not read the full contents...\n";
		}
		else
			std::cerr << "File is empty or invalid!\n";
	}
	else
		std::cerr << "Cannot open the file!\n";

	return std::nullopt;
}

std::vector<std::string_view> SplitString(std::string_view str, char delim)
{
	std::vector<std::string_view> output;

	for (auto first = str.begin(), second = str.begin(), last = str.end(); second != last && first != last; first = second + 1)
	{
		second = std::find(first, last, delim);

		//output.emplace_back(str.substr(std::distance(str.begin(), first), std::distance(first, second))); // we might get empty string views here, but that's ok in the case of CSV reader
		output.emplace_back(&*first, std::distance(first, second));
	}

	return output;
}

std::vector<std::string_view> SplitLines(std::string_view sv)
{
	ScopeTimer _t(__func__);
	return SplitString(sv, '\n');
}

class OrderRecord
{
public:
	OrderRecord() = default;
	OrderRecord(size_t id, size_t prodId, std::string date, std::string coupon, double unitPrice, double discount, unsigned int quantity) noexcept
		: mId(id)
		, mProductId(prodId)
		, mDate(std::move(date))
		, mCouponCode(std::move(coupon))
		, mUnitPrice(unitPrice)
		, mDiscount(discount)
		, mQuantity(quantity)
	{ }

	double CalcRecordPrice() const noexcept { return mQuantity * mUnitPrice*(1.0 - mDiscount); }

public:
	// not enum class so that we can easily use it as array index
	enum Indices { ID, PRODUCT_ID, DATE, COUPON, UNIT_PRICE, DISCOUNT, QUANTITY, ENUM_LENGTH };
	static const size_t INVALID_ID{ 0 };

private:
	size_t mId{ INVALID_ID };
	size_t mProductId{ INVALID_ID };
	std::string mDate;
	std::string mCouponCode;
	double mUnitPrice{ 0.0 };
	double mDiscount{ 0.0 }; // 0... 1.0
	unsigned int mQuantity{ 0 };
};

template<typename T> std::optional<T> TryConvert(std::string_view sv) noexcept
{
	T value{ };
	const auto res = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (res.ec == std::errc{})
		return value;

	return std::nullopt;
}

OrderRecord LineToRecord(std::string_view sv)
{
	auto columns = SplitString(sv, ';');
	if (columns.size() == static_cast<size_t>(OrderRecord::ENUM_LENGTH)) // assuming we also might encounter empty "columns"
	{
		const auto id = TryConvert<size_t>(columns[OrderRecord::ID]);
		const auto prodId = TryConvert<size_t>(columns[OrderRecord::PRODUCT_ID]);
		const auto unitPrice = TryConvert<double>(columns[OrderRecord::UNIT_PRICE]);
		const auto discount = TryConvert<double>(columns[OrderRecord::DISCOUNT]);
		const auto quantity = TryConvert<unsigned int>(columns[OrderRecord::QUANTITY]);

		if (id && prodId && unitPrice && discount && quantity)
		{
			return {*id,
					*prodId,
					std::string(columns[OrderRecord::DATE]),
					std::string(columns[OrderRecord::COUPON]),
					*discount,
					*unitPrice,
					*quantity };
		}
	}
	return { }; // default, invalid record
}

std::vector<OrderRecord> LinesToRecords(const std::vector<std::string_view>& lines, bool parallel)
{
	ScopeTimer _t(parallel ? "LinesToRecords par" : "LinesToRecords seq");

	std::vector<OrderRecord> outRecords;

	if (parallel)
	{
		// we need to resize the vector, creating "empty" records, as there's no way to use back inserter in a parallel fasion efficiently
		outRecords.resize(lines.size());

		// hacky?
		/*const auto start = outRecords.data();
		std::for_each(std::execution::par, std::begin(outRecords), std::end(outRecords), [start, &lines](PurchaseRecord& rec) {
			rec.InitFromSVCLine(lines[&rec - start]);
		});*/

		// cleaner, but probably more copies:
		std::transform(std::execution::par, std::begin(lines), std::end(lines), std::begin(outRecords), LineToRecord);
	}
	else
	{
		outRecords.reserve(lines.size());
		std::transform(lines.begin(), lines.end(), std::back_inserter(outRecords), LineToRecord);
	}


	return outRecords;
}

std::vector<OrderRecord> LoadRecords(const std::filesystem::path& filename, bool parallel)
{
	ScopeTimer _t(__func__);
	const auto content = GetFileContents(filename);

	if (!content)
	{
		std::cerr << "Cannot read a file...\n";
		return { };
	}

	std::cout << "string size: " << content->size() << '\n';

	const auto lines = SplitLines(*content);

	return LinesToRecords(lines, parallel);
}

double CalcTotalOrder(const std::vector<OrderRecord>& records, bool parallel)
{
	ScopeTimer _t("total order, seq");

	if (parallel)
	{
		return std::transform_reduce(
			std::execution::par,
			std::begin(records), std::end(records),
			0.0,
			std::plus<>(),
			[](const OrderRecord& rec) {
				return rec.CalcRecordPrice();
			}
		);
	}
	
	return std::accumulate(std::begin(records), std::end(records),	0.0, [](double val, const OrderRecord& rec) {
		return val + rec.CalcRecordPrice();
		}
	);
}

int main(int argc, const char** argv)
{
	if (argc == 1)
	{
		std::cerr << "CSVReader.exe filename par\n";
		return 1;
	}
	
	const bool parallel = argc > 2 ? atoi(argv[2]) > 0 : false;
	
	const auto records = LoadRecords(argv[1], parallel);

	const auto totalValue = CalcTotalOrder(records, parallel);
	std::cout << totalValue << '\n';

	return 0;
}