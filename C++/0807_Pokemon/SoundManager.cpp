#include "stdafx.h"

SoundManager::SoundManager()
{
	InitSound();
}

SoundManager::~SoundManager()
{
	DeleteAll();
	m_System->release();
	m_System->close();
}

//	�ʱ�ȭ
void	SoundManager::InitSound()
{
	//	���� �ý��� ���
	FMOD::System_Create(&m_System);

	m_System->init( 
		CHAR_MAX,			//	���� ����� ���� ����
		FMOD_INIT_NORMAL,	//	�ý��� �⺻ �ɼ�
		nullptr );			//	�߰� ����̹� ����( ���� nullptr )

	//	���� ����
	m_BGVolume		=	1.0f;
	m_EffectVolume	=	1.0f;

	CreateSound("Sound/03 Opening.mp3", TYPE_BGSOUND);
}

//	���� ���� ����
void	SoundManager::DeleteAll(void)
{
	//	������� ä�� ����
	BGPlayListClear();
	EffectPlayListClear();

	//	���� ����Ʈ�� �ִ� ��� ���� ���� ����
	auto Iter = m_SoundList.begin();

	while( m_SoundList.empty() == false )
	{
		SoundTrackInfo	&Info = Iter->second;
		
		Info.m_Sound->release();

		Iter = m_SoundList.erase(Iter);
	}

	//	���� ����Ʈ�� �ߺ� üũ ����Ʈ ����
	m_SoundList.clear();	
	m_CheckList.clear();
}

//	������Ʈ( �����Ⱓ�� �ѹ��� �ؾ� �ݺ���� ���� )
void	SoundManager::Update()
{
	//	�ݺ���� ������ ���� ������Ʈ
	m_System->update();

	//	���� ������� ä�� Ȯ��
	BGPlayListUpdate();
	EffectPlayListUpdate();
}

//	���� ����
SOUND_INDEX	SoundManager::CreateSound(const char *_FilePath, TYPESOUND _Type)
{
	//	�ε��� ��ȣ�� ��ġ�� �ʱ� ���ؼ� ����ϴ� ����
	static	SOUND_INDEX	Index = 1;

	//	�ߺ� ����Ʈ�� ���� Ȯ��
	auto	Find = m_CheckList.find(_FilePath);

	//	�̹� �ִ� ��� �ش� ���� �ε��� ��ȯ
	if (Find != m_CheckList.end())
	{
		return Find->second;
	}

	//	Ÿ�Կ� ���� �÷��� ����
	int	Flag = FMOD_DEFAULT;

	if (_Type == TYPE_EFFECTSOUND)
	{
		Flag |= FMOD_LOOP_OFF;
	}
	else
	{
		Flag |= FMOD_LOOP_NORMAL;
	}

	//	���� ����
	SoundTrackInfo	Data;

	m_System->createSound(_FilePath, Flag, nullptr, &Data.m_Sound );

	Data.m_PlayType = _Type;

	//	���� ����Ʈ�� ����
	m_SoundList.insert( std::make_pair( Index, Data) );
	//	�ߺ� ����Ʈ�� ����
	m_CheckList.insert(std::make_pair(_FilePath, Index));

	//	�ش� �ε��� ��ȯ
	return Index++;
}

//	�ش� ���� ���
bool	SoundManager::PlaySoundTrack(SOUND_INDEX _Index)
{
	//	�ش� �ε��� �˻�
	SoundTrackInfo		*Info = FindSound(_Index);

	if ( Info == nullptr)
	{
		return false;
	}

	//	�ش� ä�η� ���� ���  �Ͻ����� ���·�
	FMOD_CH	Channel = nullptr;
	m_System->playSound(FMOD_CHANNEL_REUSE, Info->m_Sound, true, &Channel);

	//	���� ����
	if( Info->m_PlayType == TYPE_BGSOUND )
	{
		Channel->setVolume( m_BGVolume );
		m_BGPlayList.push_back(Channel);
	}
	else
	{
		Channel->setVolume( m_EffectVolume );
		m_EffectPlayList.push_back(Channel);
	}

	//	���� ���
	Channel->setPaused(false);

	return true;
}

//	�ε����� ���� ���� ã��
SoundManager::SoundTrackInfo*		SoundManager::FindSound(SOUND_INDEX _Index)
{
	auto Find = m_SoundList.find(_Index);

	if( Find == m_SoundList.end() )
	{
		return nullptr;
	}

	return &(Find->second);
}

//	�ش� ä�� ���� ������Ʈ
void		SoundManager::ChannelUpdate(PLAYLIST &_List)
{
	auto		iter		= _List.begin();
	bool		IsPlaying	=	false;

	while( iter != _List.end() )
	{
		FMOD_CH	&Chanel	=	*iter;

		Chanel->isPlaying( &IsPlaying);

		if( IsPlaying == false )
		{
			iter	= _List.erase( iter );
		}

		else
		{
			iter++;
		}
	}
}

//	������� ����� ������Ʈ
void SoundManager::BGPlayListUpdate(void)
{
	ChannelUpdate(m_BGPlayList);
}

//	������� ȿ���� ������Ʈ
void SoundManager::EffectPlayListUpdate(void)
{
	ChannelUpdate(m_EffectPlayList);
}

//	�ش� ����Ʈ ä�� û��
void SoundManager::ChannelClear(PLAYLIST &_List)
{
	auto		iter		= _List.begin();
	bool		IsPlaying	=	false;

	while( _List.empty() == false )
	{
		FMOD_CH	&Channel = *iter;

		Channel->isPlaying( &IsPlaying);

		if(IsPlaying ==	true )
		{
			Channel->stop();
		}

		iter	= _List.erase( iter );
	}
}

//	������� ����� û��
void		SoundManager::BGPlayListClear()
{
	ChannelClear(m_BGPlayList);
}
//	������� ȿ���� û��
void		SoundManager::EffectPlayListClear()
{
	ChannelClear(m_EffectPlayList);
}

//	�ش� ��� ä�θ���Ʈ�� ���� ����
float SoundManager::SetVolume(float _Volume, PLAYLIST &_List)
{
	if (_Volume > 1.0f)
	{
		_Volume = 1.0f;
	}
	else if (_Volume < 0)
	{
		_Volume = 0;
	}

	for (auto &i : _List)
	{
		i->setVolume(_Volume);
	}

	return _Volume;
}

float	SoundManager::SetBGVolume(float _Volume)
{
	return m_BGVolume = SetVolume(_Volume, m_BGPlayList);
}

float	SoundManager::SetEffectVolume(float _Volume)
{
	return m_EffectVolume = SetVolume(_Volume, m_EffectPlayList);
}