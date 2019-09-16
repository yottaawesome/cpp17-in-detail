// dynamicExceptionSpecRemoved.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

// when compiling with C++17 language flag GCC emits:
// error: ISO C++1z does not allow dynamic exception specifications
void fooThrowsInt(int a) throw(int) {   
   if (a == 0)  
      throw 1;  
}  

int main() {
	
}