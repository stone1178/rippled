#include "SerializedTypes.h"
#include "RippleAddress.h"
#include "OrderBookDB.h"
#include <boost/shared_ptr.hpp>

#if 0
//
// This is a very simple implementation. This can be made way better.
// We are simply flooding from the start. And doing an exhaustive search of all paths under maxSearchSteps. An easy improvement would
be to flood from both directions.
//

class PathOption
{
public:
	typedef boost::shared_ptr<PathOption> pointer;

	STPath		mPath;
	bool		mCorrectCurrency;	// for the sorting
	uint160		mCurrencyID;		// what currency we currently have at the end of the path
	uint160		mCurrentAccount;	// what account is at the end of the path
	int			mTotalCost;			// in send currency
	STAmount	mMinWidth;			// in dest currency
	float		mQuality;

	PathOption(uint160& srcAccount,uint160& srcCurrencyID,const uint160& dstCurrencyID);
	PathOption(PathOption::pointer other);
};
#endif

class Pathfinder
{
	uint160			mSrcAccountID;
	uint160			mDstAccountID;
	STAmount		mDstAmount;
	uint160			mSrcCurrencyID;
	uint160			mSrcIssuerID;

	OrderBookDB		mOrderBook;
	Ledger::pointer mLedger;

//	std::list<PathOption::pointer> mBuildingPaths;
//	std::list<PathOption::pointer> mCompletePaths;

//	void addOptions(PathOption::pointer tail);

	// returns true if any building paths are now complete?
	bool checkComplete(STPathSet& retPathSet);

//	void addPathOption(PathOption::pointer pathOption);

public:
	Pathfinder(const RippleAddress& srcAccountID, const RippleAddress& dstAccountID, const uint160& srcCurrencyID, const uint160& srcIssuerID, const STAmount& dstAmount);

	// returns false if there is no path. otherwise fills out retPath
	bool findPaths(int maxSearchSteps, int maxPay, STPathSet& retPathSet, bool bAllowEmpty);
};
// vim:ts=4