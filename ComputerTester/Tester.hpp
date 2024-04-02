class Tester {
private:
	bool allocated;
	LPCWSTR result;
protected:
	void SetResult(LPCWSTR result, bool allocated);
public:
	Tester();
	virtual void DoTest();
	LPCWSTR GetResult();
};