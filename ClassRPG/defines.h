#pragma once

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] p; p = nullptr}

#define DECLARE_SINGLE(Type)\
	private:\
		static Type* m_pInst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_pInst)\
				m_pInst = new Type;\
			return m_pInst;\
		}\
		static void Destroy()\
		{\
			SAFE_DELETE(m_pInst);\
		}\
	private:\
		Type();\
		~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_Inst = nullptr;

#define GET_SINGLE(Type)	Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::Destroy()