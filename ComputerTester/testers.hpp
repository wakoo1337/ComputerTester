#pragma once
class InetConnectedTester : public Tester {
	void DoTest() override;
public:
	InetConnectedTester();
};

class AntivirusWorkTester : public Tester {
	void DoTest() override;
public:
	AntivirusWorkTester();
};

class FireWallTester : public Tester {
	void DoTest() override;
public:
	FireWallTester();
};

class FireWallWorkTester : public Tester {
	void DoTest() override;
public:
	FireWallWorkTester();
};

class CheckInstallAntivirus : public Tester {
	void DoTest() override;
public:
	CheckInstallAntivirus();
};

class DiskSpaceTester : public Tester {
	void DoTest() override;
public:
	DiskSpaceTester();
};

class EicarDownloadTester : public Tester {
	void DoTest() override;
public:
	EicarDownloadTester();
};

class InetSpeedTester : public Tester {
	void DoTest() override;
public:
	InetSpeedTester();
};
