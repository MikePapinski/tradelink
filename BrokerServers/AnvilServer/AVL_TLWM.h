#pragma once
#include "TradeLibFast.h"
#include "TLStock.h"
#include "TLIndex.h"
#include "AnvilUtil.h"
#include "BusinessApi.h"
#include <vector>
using namespace std;

namespace TradeLibFast
{
	class AVL_TLWM :
		public TLServer_WM,
		public Observer
	{
	public:
		AVL_TLWM(void);
		~AVL_TLWM(void);
		vector<int> GetFeatures();
		int AccountResponse(CString clientname);
		int PositionResponse(CString account,CString clientname);
		int RegisterStocks(CString clientname);
		static AVL_TLWM* GetInstance() { return instance; };
		

	protected:
		static AVL_TLWM* instance;
		vector <Observer*> subs;
		vector<CString> subsym;
		vector<Order*> ordercache;
		const StockBase* preload(CString symbol);

		int BrokerName(void);
		int SendOrder(TLOrder order);

		// account monitoring stuff
		vector<Observable*> accounts;
		int cacheOrder(Order* o);
		bool hasOrder(unsigned int  TLid);
		int AnvilId(unsigned int TLOrderId);
		virtual void Process(const Message* message, Observable* from, const Message* additionalInfo);

		void RemoveUnused();
		void RemoveSub(CString stock);
		bool isIndex(CString sym);
		bool hasHammerSub(CString symbol);
		int SubIdx(CString symbol);
		int ClearClient(CString client);
		int ClearStocks(CString client);


	};
}



