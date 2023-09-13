#include "Ground.h"
#include "../../SystemTypes.h"
#include "DxLib.h"

Ground::Ground()
{
}

Ground::Ground(int width, int height)
	:stage_width(width), stage_height(height)
{
}

Ground::~Ground()
{
	//Finalize();
}

void Ground::Initialize()
{
	__super::Initialize();
	// �摜�̓ǂݍ���
	ground_graphics[0] = LoadGraph(_T("Resources/Images/mapchip_037.bmp"));
	ground_graphics[1] = LoadGraph(_T("Resources/Images/mapchip_038.bmp"));
	ground_graphics[2] = LoadGraph(_T("Resources/Images/mapchip_039.bmp"));

	ground_graphics[3] = LoadGraph(_T("Resources/Images/mapchip_040.bmp"));
	ground_graphics[4] = LoadGraph(_T("Resources/Images/mapchip_041.bmp"));
	ground_graphics[5] = LoadGraph(_T("Resources/Images/mapchip_042.bmp"));

	ground_graphics[6] = LoadGraph(_T("Resources/Images/mapchip_043.bmp"));
	ground_graphics[7] = LoadGraph(_T("Resources/Images/mapchip_044.bmp"));
	ground_graphics[8] = LoadGraph(_T("Resources/Images/mapchip_045.bmp"));

	//vector<int> ground_mapchip = {
	//	//0,0,0,0,0,
	//	1,1,1,1,1,
	//	//0,0,0,0,0,
	//	0,0,0,0,0,
	//	0,0,0,1,0,
	//	1,1,1,1,1,
	//	1,1,1,1,1,
	//};
	//ground_data = ground_mapchip;
}

void Ground::Update(float delta_seconds)
{
	__super::Update(delta_seconds);
}

void Ground::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);

	/*int stage_width = 5;
	int stage_height = 5;*/

	for (int stage_y = 0; stage_y < stage_height; stage_y++)
	{
		for (int stage_x = 0; stage_x < stage_width; stage_x++)
		{
			int index = stage_x + stage_y * stage_width;
			int one_step_up = index - stage_width;
			int two_step_up = index - stage_width * 2;
			const int GROUND_DELTA = TOP_GROUND_PX_HEIGHT - GROUND_SIDE_PX_LENGTH;
			boolean isGround = ground_data[index] == 1;

			switch (ground_data[index])
			{
				//�E�[�A���[�̂��Ƃ͍l�����Ɏ���
			case 1:
				//�ŏ�i�̏ꍇ
				if (index < stage_width)
				{
					//48-32=12px����i-�����j�ɕ`��
					DrawGraph(x + stage_x * GROUND_SIDE_PX_LENGTH, y - GROUND_DELTA, ground_graphics[1], true);
				}
				else
				{
					//��i�F��i��ione_step_up�j��1�łȂ��Ƃ�
					if (ground_data[one_step_up] != 1)
					{
						DrawGraph(x + stage_x * GROUND_SIDE_PX_LENGTH, y + stage_y * GROUND_SIDE_PX_LENGTH, ground_graphics[1], true);
					}
					//���i�F��i��ione_step_up�j��1�̂Ƃ�
					//if (ground_data[one_step_up] == 1)
					else
					{
						if (ground_data[two_step_up] != 1)
						{
							DrawGraph(x + stage_x * GROUND_SIDE_PX_LENGTH, y + stage_y * GROUND_SIDE_PX_LENGTH + GROUND_DELTA, ground_graphics[4], true);
						}
						else
						{
							DrawGraph(x + stage_x * GROUND_SIDE_PX_LENGTH, y + stage_y * GROUND_SIDE_PX_LENGTH, ground_graphics[4], true);
						}
					}
				}
				break;
			}
			//printfDx("%d,", ground_data[index]);
		}
		//printfDx("\n");
	}

	//y-1=0�̂Ƃ��A��ӂ�`�悷��
//	DrawGraph(x, y, ground_graphics[0], true);
//	DrawGraph(x + ground_graphic_side_length, y, ground_graphics[1], true);
//	DrawGraph(x + ground_graphic_side_length * 2, y, ground_graphics[2], true);
//
//	//y-1�̒l��1�̂Ƃ��A��ӂƉ��Ӂi0~3,7~9�͕`�悹���A4~6��3��`�悷��?
//	DrawGraph(x, y + top_ground_graphic_height, ground_graphics[3], true);
//	DrawGraph(x + ground_graphic_side_length, y + top_ground_graphic_height, ground_graphics[4], true);
//	DrawGraph(x + ground_graphic_side_length * 2, y + top_ground_graphic_height, ground_graphics[5], true);
//
//	int under = top_ground_graphic_height + ground_graphic_side_length;
//	DrawGraph(x, y + under, ground_graphics[6], true);
//	DrawGraph(x + ground_graphic_side_length, y + under, ground_graphics[7], true);
//	DrawGraph(x + ground_graphic_side_length * 2, y + under, ground_graphics[8], true);
}

void Ground::Finalize()
{
	__super::Finalize();
}