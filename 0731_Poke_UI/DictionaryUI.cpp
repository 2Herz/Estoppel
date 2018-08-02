#include "DictionaryUI.h"

typedef TextUI Text;

DictionaryUI::DictionaryUI()
{
}

DictionaryUI::~DictionaryUI()
{
	IMG_MGR->Destroy();
}

void DictionaryUI::Init(HWND _hWnd)
{
	IMG_MGR->SethWnd(_hWnd);
	IMG_MGR->OpenImg("Image/Dic_01.bmp", WIN_WIDTH, WIN_HEIGHT);

	auto img = IMG_MGR->GetImg("Dic_01");

	if (img != nullptr)
	{
		img->SetTrans();
	}
}

void DictionaryUI::Render_Main_Dictionary(HDC _hdc, int _width, int _height, bool _select)
{
	Text text;
	HDC _BGDC = IMG_MGR->GetImg("Dic_01")->GetImgDC();
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	for (int i = 0; i < m_ViewCount + 1; i++)
	{
		textList.push_back(i);
	}

	while (true)
	{
		if (!m_isDraw)
		{
			for (int i = 0; i < m_ViewCount; i++)
			{
				if (i + m_TopIndex >= (signed)textList.size()) break;
				text.TextBox(_hdc, m_ImgPos.x + 250, m_ImgPos.y + 11, Dictionary_Title, m_WordSize, WHITE);
				//	포켓몬 목록 - 고정 포커스
				if (m_isFocus == false)
				{
					text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_category[0], m_WordSize, ORANGE);
					text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 166, m_category[1], m_WordSize, ORANGE);
					text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 206 + (m_WordSize * 9), m_category[12], m_WordSize, ORANGE);
					text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 206 + (m_WordSize * 14) + 30, m_category[17], m_WordSize, ORANGE);
				}

				//	비고정 포커스
				if (!m_isFocus)
				{
					//	번호 순
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 120, m_category[2], m_WordSize, BLACK);
					//	초원 ~ 희귀한
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206, m_category[3], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize), m_category[4], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 2), m_category[5], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 3), m_category[6], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 4), m_category[7], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 5), m_category[8], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 6), m_category[9], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 7), m_category[10], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 8), m_category[11], m_WordSize, BLACK);
					//	정렬
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 10), m_category[13], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 11), m_category[14], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 12), m_category[15], m_WordSize, BLACK);
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 13), m_category[16], m_WordSize, BLACK);
					//	기타
					text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 15) + 30, m_category[18], m_WordSize, BLACK);
				}

				text.TextBox(_hdc, m_ImgPos.x + 750, m_ImgPos.y + 595, m_category[19], (m_WordSize - 5), WHITE);
				text.TextBox(_hdc, m_ImgPos.x + 865, m_ImgPos.y + 595, m_category[20], (m_WordSize - 5), WHITE);
				text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 113, m_category[21], (m_WordSize - 5), BLACK);
				text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 203, m_category[22], (m_WordSize - 5), BLACK);

				//	선택했을 때
				if (m_CursorIndex == i + m_TopIndex)
				{
					if (_select == false) return;

					auto select = IMG_MGR->GetImg("Select");
					select->AniRender(_hdc, 0, m_ImgPos.x + 80, m_ImgPos.y + 120);


					switch (_select)
					{
					case DS_POKEMON_LIST:
					{
						if (m_isFocus == false)
						{
							text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_category[0], m_WordSize, ORANGE);
						}
					}
					break;
					case DS_LIST:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 120, m_category[2], m_WordSize, BLACK);
						}
					}
					break;
					case DS_GRASSLAND:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206, m_category[3], m_WordSize, BLACK);
						}
					}
					break;

					case DS_FOREST:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize), m_category[4], m_WordSize, BLACK);
						}
					}break;
					case DS_WATERFRONT:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize), m_category[5], m_WordSize, BLACK);
						}
					}
					break;
					case DS_SEA:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 2), m_category[6], m_WordSize, BLACK);
						}
					}
					break;
					case DS_CAVE:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 3), m_category[7], m_WordSize, BLACK);
						}
					}
					break;
					case DS_MOUNTAIN:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 4), m_category[8], m_WordSize, BLACK);
						}
					}
					break;
					case DS_WILDERNESS:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 5), m_category[9], m_WordSize, BLACK);
						}
					}
					break;
					case DS_CITY:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 6), m_category[10], m_WordSize, BLACK);
						}
					}
					break;
					case DS_RARE:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 7), m_category[11], m_WordSize, BLACK);
						}
					}
					break;
					case DS_SORT:
					{
						if (m_isFocus == false)
						{
							text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 206 + (m_WordSize * 9), m_category[12], m_WordSize, ORANGE);
						}
					}
					break;
					case DS_SORT_ORDER:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 10), m_category[13], m_WordSize, BLACK);
						}
					}
					break;
					case DS_SORT_TYPE:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 11), m_category[14], m_WordSize, BLACK);
						}
					}
					break;
					case DS_SORT_WEIGHT:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 12), m_category[15], m_WordSize, BLACK);
						}
					}
					break;
					case DS_SORT_SIZE:
					{
						if (!m_isFocus)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 13), m_category[16], m_WordSize, BLACK);
						}
					}
					break;
					case DS_ETC:
					{
						if (m_isFocus == false)
						{
							text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 15) + 30, m_category[18], m_WordSize, BLACK);
						}

					}break;
					}

					if (KEYMGR.OnceKeyDown(VK_UP))
					{
						if (m_CursorIndex < (signed)textList.size() - 1) m_CursorIndex++;
					}
					if (KEYMGR.OnceKeyDown(VK_DOWN))
					{
						if (m_CursorIndex > 0) m_CursorIndex--;
					}

					if (m_CursorIndex < m_TopIndex)
						m_TopIndex = m_CursorIndex;

					if (m_CursorIndex >= m_TopIndex + m_ViewCount)
						m_TopIndex = m_CursorIndex - m_ViewCount + 1;

					m_isDraw = true;
				}
			}
			m_isDraw = false;
		}
	}
}

void DictionaryUI::Render_Dictionary_List(HDC _hdc, int width, int _height)
{

	Text text;
	auto img = IMG_MGR->GetImg("Dic_01");
	text.TextBox(_hdc, 250, 6, "포켓몬    목록", 50, WHITE);
	text.TextBox(_hdc, 100, 60, "No001  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 110, "No002  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 160, "No003  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 210, "No004  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 260, "No005  - - - - -", 50, BLACK);
}

void DictionaryUI::Render_Dictionary_GrassLand(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Forest(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_WaterFront(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sea(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Cave(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Mountain(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Wilderness(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_City(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Rare(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Order()
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Type(int _select, int _type)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Weight(int _select, int _weight)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Size(int _select, int _size)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}