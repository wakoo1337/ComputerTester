class Tester {
protected:
	LPCWSTR result;
public:
	Tester();
	virtual void DoTest();
	LPCWSTR GetResult();
};