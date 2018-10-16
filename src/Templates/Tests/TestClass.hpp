#ifndef TEST_TESTCLASS_HPP
#define TEST_TESTCLASS_HPP

class TestClass
{
public:
	TestClass();
	TestClass(const TestClass &testClass);
	TestClass(TestClass &&testClass) noexcept;
	TestClass(long initL, int initI
			, short initS, char initC);
	~TestClass();
	TestClass &operator=(const TestClass &testClass);
	TestClass &operator=(TestClass &&testClass) noexcept;

	bool operator==(const TestClass &testClass) const;

	bool operator!=(const TestClass &testClass) const
	{
		return !operator==(testClass);
	}

	operator bool() const
	{
		return l && i && s && c;
	}

	long &getLong();
	const long &getLong() const;

	int &getInt();
	const int &getInt() const;

	short &getShort();
	const short &getShort() const;

	char &getChar();
	const char &getChar() const;

private:
	void clean();

	long *l;
	int *i;
	short *s;
	char *c;
};

#endif // TEST_TESTCLASS_HPP
