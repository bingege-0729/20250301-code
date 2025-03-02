#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int Max_rooms = 10;
int Max_guest = 20;
struct rooms_info {
	int roomNumber;
	char roomType[20];
	float price;
	int isBooked;
	char host[20];
};
struct guest {
	char name[50];
	char gender[4];
	int sum;
	char whether_VIP[5];
};
//2.初始化房间信息
void initializeRooms(struct rooms_info room[], int *numRooms) {
	int i;
	*numRooms = 0;
	for (i = 0; i < Max_rooms; i++) {
		room[i].roomNumber = 101 + i;
		strcpy(room[i].host, "无人" );
		if (i < Max_rooms / 2) {
			strcpy(room[i].roomType, "单人间");
			room[i].price = 200.0;
			

		} else {
			strcpy(room[i].roomType, "双人间");

			room[i].price = 300.0;

		}
		room[i].isBooked = 0;
		(*numRooms)++;

	}

}
//显示房间信息
void extra_displayingRooms(struct rooms_info room[], int *numRooms) {
	int i;
	printf("以下为本酒店已订购房间情况：\n");
	printf("房号   ");
	printf("房间类型  ");
	printf("房间价格  ");
	printf("房间状态\n");
	for (i = 0; i < *numRooms; i++) {
		printf("%d   ", room[i].roomNumber);
		printf("%s    ", room[i].roomType);
		printf("%.2lf    ", room[i].price);
		printf("%d\n", room[i].isBooked);
	}
}
//1.酒店专门显示房间信息
void displayingRooms(struct rooms_info room[], int *numRooms) {
	int i;
	printf("以下为本酒店已订购房间情况：\n");
	printf("房号   ");
	printf("房间类型  ");
	printf("房间价格  ");
	printf("房间状态  ");
	printf("房间租户\n");
	for (i = 0; i < *numRooms; i++) {
		printf("%d   ", room[i].roomNumber);
		printf("%s    ", room[i].roomType);
		printf("%.2lf      ", room[i].price);
		printf("%d    ", room[i].isBooked);
		printf("     %s\n", room[i].host);
	}
}
//顾客系统
//1.注册
void regist_name(struct guest name[], int *numGuest) {
	printf("欢迎光临本酒店！\n");
	printf("请输入您的姓名：");
	scanf("%s", name[*numGuest].name);
	printf("请输入您的性别：");
	scanf("%s", name[*numGuest].gender);
	name[*numGuest].sum = 0;
	strcpy(name[*numGuest].whether_VIP, "非VIP");
	(*numGuest)++;
}


//3.显示客户信息
void displaying_guest(struct guest VIP[], int index) {
	printf("姓名：%s\t", VIP[index].name);
	printf("性别：%s\t", VIP[index].gender);
	printf("账户余额：%d\t", VIP[index].sum);
	printf("用户等级：%s\t", VIP[index].whether_VIP);
	printf("\n");
}


//2.VIP系统
void VIP_system(struct guest VIP[], int index) {
	printf("尊贵的VIP用户，您好！\n");
	displaying_guest(VIP, index);
}


//4.判断是否为VIP
void whether_VIP(struct guest VIP[], int *numGuest, struct rooms_info name[], int *numRooms) {
	int i, j;
	int isVIP = 0;
	if (*numGuest != 0) {
		for (i = 0; i < *numGuest; i++) {
			for (j = 0; j < *numRooms; j++) {
				//不可使用“==”，有错误，用strcmp
				if (strcmp(VIP[i].name, name[j].host) == 0) {
					strcpy(VIP[i].whether_VIP, "VIP");
					VIP_system(VIP, i);
					isVIP = 1;
					break;
				}
			}
			if (!isVIP) {
				strcpy(VIP[i].whether_VIP, "非VIP");
				displaying_guest(VIP, i);
			}
		}
	}

}
//5.订房系统
void book_room(struct rooms_info room[], int *numRooms, struct guest guest[], int *numGuest) {
	displayingRooms(room, numRooms); //需要的是int *类型的
	int roomNumber;
	printf("请输入要预定的房间号：");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 0) {
				room[i].isBooked = 1;
				strcpy(room[i].host, guest[*numGuest - 1].name);
				printf("房间预定成功！\n");
				if(roomNumber/2!=0){
					guest[i].sum-=200;
				}else{
					guest[i].sum-=300;
				}
				
				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("该房间已被预订，请选择其他房间。\n");
				return;
			}
		}
	}
	printf("未找到该房间号，请重新输入：");
}
//退房系统
void check_out(struct rooms_info room[], int *numRooms) {
	int roomNumber;
	printf("请输入要退房的房间号：");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 1) {
				room[i].isBooked = 0;
				strcpy(room[i].host, "无人");
				printf("退房成功！\n");
				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("该房间未被预订，无需退房。\n");
				return;
			}
		}
	}
	printf("未找到该房间号，请重新输入。\n");
}
//充值
void charge(struct guest guest[], int index) {
	displaying_guest(guest, index);
	int s;
	int choice;
	printf("1.充值\n");
	printf("2.取消\n");
	scanf("%d", &choice);
	while (choice != 1 && choice != 2) {
		printf("无效输入，请重新选择：");
		scanf("%d", &choice);
	}
	if (choice == 1) {
		printf("请输入需要充值的数额：");
		scanf("%d", &s);
		guest[index].sum += s;
		if (guest[index].sum > 500) {
			strcpy(guest[index].whether_VIP, "VIP");
			displaying_guest(guest, index);
		}
	} else {
		printf("已取消充值操作。\n");
	}
}

// 修正后的guest_system函数
void guest_system(struct guest guest[], struct rooms_info room[], int *numGuest, int *numRooms) {
	int choice;
	regist_name(guest, numGuest); // 传递指针
	whether_VIP(guest, numGuest, room, numRooms); // 参数顺序修正
	do {
		displayingRooms(room, numRooms); //需要的是int *类型的
		printf("1. 预订房间\n");
		printf("2. 退房\n");
		printf("3.充值\n");
		printf("0. 退出旅客系统\n");
		printf("请做出选择：");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				book_room(room, numRooms, guest, numGuest); // 参数修正
				break;
			case 2:
				check_out(room, numRooms); // 参数修正
				break;
			case 3:
				charge(guest, *numGuest - 1);
				break;
			case 0:
				printf("已成功退出旅客系统。\n");
				break;
			default: // 修正拼写错误
				printf("无效输入，请重新输入！\n");
		}
	} while (choice != 0);
}
int main(int argc, char *argv[]) {

	struct guest guest[Max_rooms];
	struct rooms_info room[Max_guest];
	int numGuest = 0;
	int numRooms;
	initializeRooms(room, &numRooms);//最初缺少这步，导致输出的房间信息为乱码
	guest_system(guest, room, &numGuest, &numRooms);
	return 0;
}
