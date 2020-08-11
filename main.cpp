#include<iostream>
#include<time.h>
#include<iomanip>
#define random(x) (rand()%x)
#define NUM 3

char doors[NUM] = { '0', '0','0' };

void InitDoors();

//change the door
//return true if get '1'
//else return false
bool DoChange();

//do not change the door
//return true if get '1'
//else return false
bool DoNotChange();

//Rechoose the door,means maybechange
//return true if get '1'
//else return false
bool ReChoose();

#define ELE_NUM 50
void show_process_rate(int64_t rate) {
	int64_t element_num = int(rate / (100 / ELE_NUM));
	char rate_bar[ELE_NUM+1] = { 0 };

	auto ret = [&]()->bool {
		for (int64_t i = 0; i < ELE_NUM; ++i) {
			if (i <= element_num) {
				rate_bar[i] = '=';
			}
			else {
				rate_bar[i] = ' ';
			}
		}

		for (int64_t i = ELE_NUM - 1; i >= 0; --i) {
			if ('=' == rate_bar[i] && ELE_NUM-1 != i) {
				rate_bar[i] = '>';
				break;
			}
			else if ('=' == rate_bar[i] && ELE_NUM - 1 == i) {
				break;
			}
		}
		return true;
	}();

	char show_str[200] = { 0 };
	sprintf_s(show_str, sizeof(show_str), "[%s]%0d%%", rate_bar, rate);
	std::cout << "\r";
	std::cout << show_str;
}

int main()
{
	std::cout << std::setiosflags(std::ios::fixed);
	std::cout << "input times:";
	int64_t times;
	std::cin >> times;
	int64_t hits = 0;
	double rate;

	auto replace_out = [&](const char* content, int64_t& len) {
		for (int64_t j = 0; j < len; ++j)
			std::cout << "\b";

		len = strlen(content);
		std::cout << content;
	};

	//hits time in DoChange
	hits = [&]()->int64_t {
		int64_t hit_time = 0;
		int64_t last_rate = 0;
		for (int64_t i = 0; i < times; ++i) {
			hit_time = DoChange() ? hit_time + 1 : hit_time;
			
			//char show_str[100] = { 0 };
			//sprintf_s(show_str, sizeof(show_str), "%d/%d", i+1, times);
			//replace_out(show_str, last_show_char_len);
			int64_t cur_rate = i * 100 / times;
			if (cur_rate != last_rate) {
				show_process_rate(i * 100 / times);
				last_rate = cur_rate;
			}
			//Sleep(100);
		}
		show_process_rate(100);
		return hit_time;
	}();
	rate = (double)hits / (double)times;
	std::cout << std::endl << "DoChange:" << "total(" << times << ")---hits(" << hits << ")---rate(" << std::setprecision(10) <<rate << ")" << std::endl;

	//hits time in DoNotChange
	hits = [&]()->int64_t {
		int64_t hit_time = 0;
		int64_t last_rate = 0;
		int64_t last_show_char_len = 0;
		for (int64_t i = 0; i < times; ++i) {
			hit_time = DoNotChange() ? hit_time + 1 : hit_time;

			//char show_str[100] = { 0 };
			//sprintf_s(show_str, sizeof(show_str), "%d/%d", i + 1, times);
			//replace_out(show_str, last_show_char_len);
			int64_t cur_rate = i * 100 / times;
			if (cur_rate != last_rate) {
				show_process_rate(i * 100 / times);
				last_rate = cur_rate;
			}
			//Sleep(100);
		}
		show_process_rate(100);
		return hit_time;
	}();
	rate = (double)hits / (double)times;
	std::cout << std::endl << "DoNotChange:" << "total(" << times << ")---hits(" << hits << ")---rate(" << std::setprecision(10) << rate << ")" << std::endl;
	

	//hits time in ReChoose
	hits = [&]()->int64_t {
		int64_t hit_time = 0;
		int64_t last_rate = 0;
		int64_t last_show_char_len = 0;
		for (int64_t i = 0; i < times; ++i) {
			hit_time = ReChoose() ? hit_time + 1 : hit_time;

			//char show_str[100] = { 0 };
			//sprintf_s(show_str, sizeof(show_str), "%d/%d", i + 1, times);
			//replace_out(show_str, last_show_char_len);
			int64_t cur_rate = i * 100 / times;
			if (cur_rate != last_rate) {
				show_process_rate(i * 100 / times);
				last_rate = cur_rate;
			}
			//Sleep(100);
		}
		show_process_rate(100);
		return hit_time;
	}();
	rate = (double)hits / (double)times;
	std::cout << std::endl << "ReChoose:" << "total(" << times << ")---hits(" << hits << ")---rate(" << std::setprecision(10) << rate << ")" << std::endl;
	
	system("pause");
	return 0;
}

void InitDoors() {
	char seed[NUM] = { '0','1','0' };
	uint8_t hit[NUM] = { 0,0,0 };
	for (int64_t i = 0; i < NUM; ++i) {
		while (1) {
			uint64_t key = random(NUM);
			if (NUM <= key)continue;
			if (1 == hit[key])continue;
			else {
				hit[key] = 1;
				doors[i] = seed[key];
				break;
			}
		}
	}
}

bool DoChange() {
	InitDoors();

	//choose one door
	uint64_t target = random(NUM);

	//open a 0's door
	uint64_t one_of_zero_door = [&]()->uint64_t {
		while (1) {
			uint64_t key = random(NUM);
			if (key == target)continue;
			else if ('1' == doors[key])continue;
			else {
				return key;
			}
		}
	}();

	//change the target
	uint64_t new_target = [&]()->uint64_t {
		//while (1) {
		//	uint64_t key = random(NUM);
		//	if (key == target || key == one_of_zero_door)continue;
		//	else return key;
		//}
		return NUM - target - one_of_zero_door;
	}();

	//check new_target
	return '1' == doors[new_target];
}

bool DoNotChange() {
	InitDoors();

	//choose one door
	uint64_t target = random(NUM);

	//check target
	return '1' == doors[target];
}

bool ReChoose() {
	InitDoors();

	//choose one door
	uint64_t target = random(NUM);

	//open a 0's door
	uint64_t one_of_zero_door = [&]()->uint64_t {
		while (1) {
			uint64_t key = random(NUM);
			if (key == target)continue;
			else if ('1' == doors[key])continue;
			else {
				return key;
			}
		}
	}();

	//rechoose the target
	uint64_t new_target = [&]()->uint64_t {
		while (1) {
			uint64_t key = random(NUM);
			if (key == one_of_zero_door)continue;
			else return key;
		}
	}();

	//check new_target
	return '1' == doors[new_target];
}