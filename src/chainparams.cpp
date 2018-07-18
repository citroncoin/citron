// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x23;
		pchMessageStart[1] = 0x3a;
		pchMessageStart[2] = 0x9a;
		pchMessageStart[3] = 0x1b;
		vAlertPubKey = ParseHex("04707c5d5a40205865eca68788e4f299e7aee74c55cc3e94852900289b75d1efae82da895c371134643959d90582012daa6397cf8873944fcaa56fbe1b374f58a2");
		nDefaultPort = 42012;
		nRPCPort = 42011;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.
		//
		//CBlock(hash=0000ebc8051bff80f7946f4420efb219e66f66b89fdc1df0ed8a30b428bf0033, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
		//  Coinbase(hash=59589791e1, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
		//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
		//    CTxOut(empty)
		//  vMerkleTree: 59589791e1
		const char* pszTimestamp = "Citron started at 20/4/18";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1530923014, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1530923014;
		genesis.nBits = 520159231;
		genesis.nNonce = 8515;

		hashGenesisBlock = genesis.GetHash();

		assert(genesis.hashMerkleRoot == uint256("0xcee38c62e532689c49bf68ec63a16894b7ea5149ecbd62d2e7692590ca2944db"));
		assert(hashGenesisBlock == uint256("0xfbab94a22c6c07cd6c315f7d81bc60a6da82fe192a9d84b4637b1ac9ea84b0a2"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0",  "178.128.82.39"));
		vSeeds.push_back(CDNSSeedData("1",  "178.128.80.168"));

		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		strDarksendPoolDummyAddress = "CRaVnHZizkREBg6yBzcpy6TBLn4B5GbUva";
		nLastPOWBlock = 20000000;
		nPOSStartBlock = 1000;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x93;
		pchMessageStart[1] = 0x7e;
		pchMessageStart[2] = 0x13;
		pchMessageStart[3] = 0xa7;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("048d8c71a0b56bd75b1c90f6513730d7578a786868bdce589cecb3fe2a8bddd763df5a74317c1c56bec1152d6735ac9bf793980f8c3bd164add3de0de332a2e4c6");
		nDefaultPort = 24012;
		nRPCPort = 24011;
		strDataDir = "testnet";

		// Modify the testnet genesis block so that the timestamp is valid for a later start.
		genesis.nBits = 520159231;
		genesis.nNonce = 2971;

		assert(hashGenesisBlock == uint256("0xfbab94a22c6c07cd6c315f7d81bc60a6da82fe192a9d84b4637b1ac9ea84b0a2"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 187);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}
