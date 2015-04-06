/********************************************************************************

	Structure implementing long arithmetic in C++
	Analogue to BigInteger in Java.
	Tested on many problems.

	TODO: list some problems

********************************************************************************/

struct BigInt {

	vector <int> num;

	static const int base = 1000 * 1000 * 1000;    
	static const int baseDigits = 9;
	string leadingZerosModifier;

	/****************************************************
	* CONSTRUCTONS & SETTERS
	****************************************************/

	void setLeadingZerosModifier() {
		leadingZerosModifier = "%0xd";
		leadingZerosModifier[2] = '0' + baseDigits;
	}

	void set(int value) {
		num.clear();
		if (value == 0) 
			num.push_back(0);
		while (value) {
			num.push_back(value % base);
			value /= base;
		}
	}

	void set(long long value) {
		num.clear();
		if (value == 0) 
			num.push_back(0);
		while (value) {
			num.push_back(value % base);
			value /= base;
		}
	}

	void set(string &value) {
		num.clear();
		for (int i = (int)value.length() - 1; i >= 0; i -= baseDigits) {
			int add = 0;
			for (int j = max(0, i - baseDigits + 1); j <= i; j++)
				add = add * 10 + value[j] - '0';
			num.push_back(add);
		}
	}

	void operator = (int value) {
		set(value);
	}

	void operator = (long long value) {
		set(value);
	}

	void operator = (string &value) {
		set(value);
	}

	BigInt() {
		setLeadingZerosModifier();
		set(0);
	}

	BigInt(int value) {
		setLeadingZerosModifier();
		set(value);
	}

	BigInt(string value) {
		setLeadingZerosModifier();
		set(value);
	}

	/*====================================================
	* SIZE METHODS
	====================================================*/

	//returns size of vector 
	int size() {
		return (int)num.size();
	}

	//returns length of the number
	int digitNum() {
		int result = 0;
		for (int i = 0; i < (int)num.size() - 1; i++)
			result += baseDigits;
		int lastNum = num.back();
		while (lastNum) {
			result++;
			lastNum /= 10;
		}
		return result;
	}

	/*====================================================
	* I/O
	====================================================*/

	void read() {
		string s;
		cin >> s;
		num.clear();
		for (int i = (int)s.length() - 1; i >= 0; i -= baseDigits) {
			int add = 0;
			for (int j = max(0, i - baseDigits + 1); j <= i; j++)
				add = add * 10 + s[j] - '0';
			num.push_back(add);
		}
	}

	void print() {
		printf("%d", num.back());
		for (int i = (int)num.size() - 2; i >= 0; i--)
			printf (leadingZerosModifier.c_str(), num[i]);
	}

	void println() {
		print();
		printf("\n");
	}

	string toString() {
		string result = "";
		for (int i = 0; i < (int)num.size(); i++) {
			int cur = num[i];
			for (int j = 1; j <= baseDigits; j++) {
				if (cur == 0 && i == (int) num.size() - 1)
					break;
				result.append(1, (char) '0' + cur % 10);
				cur /= 10;
			}
		}	
		reverse(result.begin(), result.end());
		return result;
	}

	/*====================================================
	* ADDITION
	====================================================*/

	void sumThis(BigInt number) {
		int carry = 0;
		for (int i = 0; i < max((int)num.size(), number.size()) || carry; i++) {
			if (i == num.size())
				num.push_back(0);
			if (i >= number.size())
				carry = num[i] + carry;
			else
				carry = num[i] + carry + number.num[i];
			num[i] = carry % base;
			carry /= base;
		}
	}

	void sumThis(int number) {
		int carry = number;
		for (int i = 0; i < (int)num.size() || carry; i++) {
			if (i == num.size())
				num.push_back(0);
			carry = num[i] + carry;
			num[i] = carry % base;
			carry /= base;
		}
	}

	BigInt sum(BigInt number) {
		BigInt result = *this;
		result.sumThis(number);
		return result;
	}

	BigInt sum(int number) {
		BigInt result = *this;
		result.sumThis(number);
		return result;
	}

	void operator += (BigInt number) {
		sumThis(number);
	}

	void operator += (int number) {
		sumThis(number);
	}

	BigInt operator + (BigInt number) {
		return sum(number);
	}

	BigInt operator + (int number) {
		return sum(number);
	}

	/*====================================================
	* SUBTRACTION
	====================================================*/

	void subThis(BigInt number) {
		int carry = 0;
		for (int i = 0; i < (int)number.size() || carry; i++) {
			if (i < (int)number.size())
				num[i] -= carry + number.num[i];
			else
				num[i] -= carry;
			if (num[i] < 0) {
				carry = 1;
				num[i] += base;
			}
			else
				carry = 0;
		}
		while (num.size() > 1 && num.back() == 0)
			num.pop_back();
	}

	void subThis(int number) {
		int carry = -number;
		for (int i = 0; carry > 0; i++) {
			num[i] -= carry;
			if (num[i] < 0) {
				carry = 1;
				num[i] += base;
			}
			else 
				carry = 0;
		}
		while (num.size() > 1 && num.back() == 0)
			num.pop_back();
	}

	BigInt sub(BigInt number) {
		BigInt result = *this;
		result.subThis(number);
		return result;
	}

	BigInt sub(int number) {
		BigInt result = *this;
		result.subThis(number);
		return result;
	}

	void operator -= (BigInt number) {
		subThis(number);
	}

	void operator -= (int number) {
		subThis(number);
	}

	BigInt operator - (BigInt number) {
		return sub(number);
	}

	BigInt operator - (int number) {
		return sub(number);
	}

	/*====================================================
	* MULTIPLICATION
	====================================================*/

	BigInt mult(BigInt number) {
		BigInt product;
		product.num.resize(num.size() + number.size());
		for (int i = 0; i < (int)num.size(); i++) {
			for (int j = 0, carry = 0; j < (int)number.size() || carry; j++) {
				long long cur = product.num[i + j] + num[i] * 1ll * (j < (int)number.size() ? number.num[j] : 0) + carry;
				product.num[i + j] = int (cur % base);
				carry = int (cur / base);
			}
		}
		while (product.size() > 1 && product.num.back() == 0)
			product.num.pop_back();
		return product;
	}

	void multThis(BigInt number) {
		*this = mult(number);
	}

	void multThis(int number) {
		int carry = 0;
		for (int i = 0; i < (int)num.size() || carry; ++i) {
			if (i == num.size())
				num.push_back (0);
			long long cur = carry + num[i] * 1ll * number;
			num[i] = int (cur % base);
			carry = int (cur / base);
		}
		while (num.size() > 1 && num.back() == 0)
			num.pop_back();
	}

	BigInt mult(int number) {
		BigInt result = *this;
		result.multThis(number);
		return result;
	}

	void operator *= (BigInt number) {
		multThis(number);
	}    

	void operator *= (int number) {
		multThis(number);
	}    

	BigInt operator * (BigInt number) {
		return mult(number);
	}

	BigInt operator * (int number) {
		return mult(number);
	}

	void multThisByPowerOfTen(int power) {
		int baseNums = power / baseDigits;
		int curLen = (int)num.size();
		num.resize(curLen + baseNums);
		for (int i = num.size() - 1; i >= baseNums; i--) {
			num[i] = num[i - baseNums];
		}
		for (int i = baseNums - 1; i >= 0; i--)
			num[i] = 0;
		power %= baseDigits;
		int multBy = (int)pow(10.0, power); 
		multThis(multBy);
	}

	/*====================================================
	* DIVISION
	====================================================*/

	void divThis(int number) {
		int carry = 0;
		for (int i= (int)num.size() - 1; i >= 0; i--) {
			long long cur = num[i] + carry * 1ll * base;
			num[i] = int (cur / number);
			carry = int (cur % number);
		}
		while (num.size() > 1 && num.back() == 0)
			num.pop_back();
	}

	BigInt div(int number) {
		BigInt result = *this;
		result.divThis(number);
		return result;
	}

	void operator /= (int number) {
		divThis(number);
	}

	BigInt operator / (int number) {
		return div(number);
	}

	void divThisByPowerOfTen(int power) {
		int baseNums = power / baseDigits;
		int curLen = (int)num.size();
		for (int i = 0; i < (int)num.size() - baseNums; i++) {
			num[i] = num[i + baseNums];
		}
		for (int i = 1; i <= baseNums; i++)
			num.pop_back();
		power %= baseDigits;
		int divBy = (int)pow(10.0, power); 
		divThis(divBy);
	}

	/*====================================================
	* MODULO
	====================================================*/

	void modThis(int number) {
		int carry = 0;
		for (int i= (int)num.size() - 1; i >= 0; i--) {
			long long cur = num[i] + carry * 1ll * base;
			num[i] = int (cur / number);
			carry = int (cur % number);
		}
		set(carry);
	}

	BigInt mod(int number) {
		BigInt result = *this;
		result.modThis(number);
		return result;
	}

	void operator %= (int number) {
		modThis(number);
	}

	BigInt operator % (int number) {
		return mod(number);
	}

	/*====================================================
	* COMPARISON
	====================================================*/

	//Returns: -1 - this number is less than argument, 0 - equal, 1 - this number is greater
	int compareTo(BigInt number) {
		if ((int)num.size() < number.size())
			return -1;
		if ((int)num.size() > number.size())
			return 1;
		for (int i = (int)num.size() - 1; i >= 0; i--) {
			if (num[i] > number.num[i])
				return 1;
			if (num[i] < number.num[i])
				return -1;
		}
		return 0;
	}

	//Returns: -1 - this number is less than argument, 0 - equal, 1 - this number is greater
	int compareTo(int number) {
		if (num.size() > 1 || num[0] > number)
			return 1;
		if (num[0] < number)
			return -1;
		return 0;
	}

	bool operator < (BigInt number) {
		return compareTo(number) == -1;
	}

	bool operator < (int number) {
		return compareTo(number) == -1;
	}

	bool operator <= (BigInt number) {
		return compareTo(number) != 1;
	}

	bool operator <= (int number) {
		return compareTo(number) != 1;
	}

	bool operator == (BigInt number) {
		return compareTo(number) == 0;
	}

	bool operator == (int number) {
		return compareTo(number) == 0;
	}

	bool operator > (BigInt number) {
		return compareTo(number) == 1;
	}

	bool operator > (int number) {
		return compareTo(number) == 1;
	}

	bool operator >= (BigInt number) {
		return compareTo(number) != -1;
	}

	bool operator >= (int number) {
		return compareTo(number) != 1;
	}

	bool operator != (BigInt number) {
		return compareTo(number) != 0;
	}

	bool operator != (int number) {
		return compareTo(number) != 0;
	}

};