#pragma once

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr}

#define DECLARE_SINGLE(Type)	\
	private:\
		static Type* m_Inst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_Inst)\
				m_Inst = new Type;\
			return m_Inst;\
		}\
		static void Destroy()\
		{\
			SAFE_DELETE(m_Inst);\
		}\
	private:\
		Type();\
		~Type();