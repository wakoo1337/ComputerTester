class Tester {
private:
	bool allocated;
	LPCWSTR result;
protected:
	void SetResult(LPCWSTR result);
	void SetResult(std::wstring &result);
public:
	Tester();
	virtual void DoTest();
	LPCWSTR GetResult();
};