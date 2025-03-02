#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//该酒店房间数量的最大值
int Max_rooms = 10;
int Max_guest = 20;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//房间主要信息
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
	int bookedRoom;
};

//显示房间信息
// 3. 显示客户信息
void displaying_guest(struct guest VIP[], int index) {
	printf("姓名：%s\t", VIP[index].name);
	printf("性别：%s\t", VIP[index].gender);
	printf("账户余额：%d\t", VIP[index].sum);
	printf("用户等级：%s\t", VIP[index].whether_VIP);
	printf("预订房间号：%d\n", VIP[index].bookedRoom);
}

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







//酒店系统


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



//3.删除房间
void delete_room(struct rooms_info room[], int *numRooms,struct guest guest[],int numGuest) {
	int i, j;
	int deletedRoom;
	printf("输入需要删除的房间码：");
	scanf("%d", &deletedRoom);
	for (i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == deletedRoom) {
			if (room[i].isBooked == 1) {
				printf("该房间已被预订，不能删除！\n");
				return;
			}
			for (j = i; j < *numRooms - 1; j++) {
				room[j].roomNumber = room[j + 1].roomNumber;
				strcpy(room[j].roomType, room[j + 1].roomType);
				room[j].isBooked = room[j + 1].isBooked;
				room[j].price = room[j + 1].price;
				strcpy(room[j].host, room[j + 1].host);
			}
			//清理顾客预定记录
			for(int k=0;k<numGuest;k++){
				if(guest[k].bookedRoom==deletedRoom){
					guest[k].bookedRoom=-1;
				}
			}
			(*numRooms)--;
			printf("删除成功！\n");
			break;
		}
	}
	if (i == *numRooms) {
		printf("未找到该房间号，删除失败！\n");
	}
	extra_displayingRooms(room, numRooms);
}



//4.增加房间
void add_room(struct rooms_info room[], int *numRooms) {
	int choice;
	int addedRoom;
	char addedroomType[20];
	double price;
	int isBooked;
	char host[20];
	do {
		printf("输入需要额外增加的房号、房间类型、房间价格以及房间状况:");
		scanf("%d", &addedRoom);
		scanf("%s", &addedroomType);
		scanf("%lf", &price);
		scanf("%d", &isBooked);
		scanf("%s", &host);
		if (*numRooms < Max_rooms) {
			room[*numRooms].roomNumber = addedRoom;
			strcpy(room[*numRooms].roomType, addedroomType);
			room[*numRooms].isBooked = isBooked;
			room[*numRooms].price = (float)price;
			strcpy(room[*numRooms].host, host);
			(*numRooms)++;
			printf("添加房号成功！\n");
		} else {
			printf("房间数量已达上限，无法添加！\n");
		}
		extra_displayingRooms(room, *numRooms);
		printf("请问是否还需要再增加？");
		printf("1.确定\n2.否认\n");
		printf("你的选择是：");
		scanf("%d", &choice);
		if (choice != 1 && choice != 2) {
			printf("输入错误，请重新输入");
			system("pause");
		}
	} while (choice != 2);
}

//5.查询
void hotel_system_search(struct rooms_info room[], int *numRooms) {
	printf("以下为本酒店已订购房间情况：\n");
	extra_displayingRooms(room, numRooms);
}


// 查找顾客信息
void search_guest_info(struct guest guest[], int numGuest) {
	char targetName[50];
	printf("请输入要查找的顾客姓名：");
	scanf("%s", targetName);
	int found = 0;
	for (int i = 0; i < numGuest; i++) {
		if (strcmp(guest[i].name, targetName) == 0) {
			displaying_guest(guest, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("未找到该顾客信息。\n");
	}
}

//6.酒店内部系统
void hotel_system(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
	int choice;
	do {
		printf("\t*1.查询房间订购情况*\t\n");
		printf("\t*2.删除房间*\t\n");
		printf("\t*3.增加房间*\t\n");
		printf("\t*4.查询顾客信息*\t\n");
		printf("\t*0.退出*\t\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				hotel_system_search(room, numRooms);//int*类型的
				break;
			case 2:
				delete_room(room, numRooms,guest,numGuest);
				break;
			case 3:
				add_room(room, numRooms);
				break;
			case 4:
				search_guest_info(guest, numGuest);
				break;
			case 0:
				printf("已成功退出\n");
				break;
			default:
				printf("无效输入，请重新输入！\n");
		}
	} while (choice != 0);
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


////3.显示客户信息
//void displaying_guest(struct guest VIP[], int index) {
//	printf("姓名：%s\t", VIP[index].name);
//	printf("性别：%s\t", VIP[index].gender);
//	printf("账户余额：%d\t", VIP[index].sum);
//	printf("用户等级：%s\t", VIP[index].whether_VIP);
//	printf("\n");
//}


//2.VIP系统
void VIP_system(struct guest VIP[], int index) {
	printf("\t*尊贵的VIP用户，您好！*\t\n");
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
	extra_displayingRooms(room, numRooms); //需要的是int *类型的
	int roomNumber;
	printf("请输入要预定的房间号：");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 0) {
				room[i].isBooked = 1;
				strcpy(room[i].host, guest[*numGuest - 1].name);
				guest[*numGuest - 1].bookedRoom = roomNumber; // 更新预订的房间号
				printf("\t*房间预定成功！*\t\n");
				if (strcmp(room[i].roomType, "单人间") == 0) {
					guest[*numGuest - 1].sum -= 200;
				} else {
					guest[*numGuest - 1].sum -= 300;
				}

				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("\t*该房间已被预订，请选择其他房间。*\t\n");
				return;
			}
		}
	}
	printf("未找到该房间号，请重新输入：");
}
//退房系统
void check_out(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
	int roomNumber;
	printf("请输入要退房的房间号：");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 1) {
				room[i].isBooked = 0;
				strcpy(room[i].host, "无人");
				for (int j = 0; j < numGuest; j++) {
					if (guest[j].bookedRoom == roomNumber) {
						guest[j].bookedRoom = -1;
					}
				}
				printf("退房成功！\n");
				extra_displayingRooms(room, &numRooms);
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
	printf("\t*1.充值*\t\n");
	printf("\t*2.取消*\t\n");
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
		printf("\t*已取消充值操作。*\t\n");
	}
}
// 修正后的guest_system函数
void guest_system(struct guest guest[], struct rooms_info room[], int *numGuest, int *numRooms) {
	int choice;
	regist_name(guest, numGuest); // 传递指针
	whether_VIP(guest, numGuest, room, numRooms); // 参数顺序修正
	do {
		displayingRooms(room, numRooms); //需要的是int *类型的
		printf("\t*1. 预订房间*\t\n");
		printf("\t*2. 退房*\t\n");
		printf("\t*3.充值*\t\n");
		printf("\t*0. 退出旅客系统*\t\n");
		printf("请做出选择:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				book_room(room, numRooms, guest, numGuest); // 参数修正
				break;
			case 2:
				check_out(room, numRooms, guest, numGuest); // 参数修正
				break;
			case 3:
				charge(guest, *numGuest - 1);
				break;
			case 0:
				printf("\t*已成功退出旅客系统。*\t\n");
				break;
			default: // 修正拼写错误
				printf("\t*无效输入，请重新输入！*\t\n");
		}
	} while (choice != 0);
}

int main(int argc, char *argv[]) {
	int choice;
	int numRooms;
	int numGuest = 0;
	struct rooms_info room[Max_rooms];
	struct guest guest[Max_guest];
	initializeRooms(room, &numRooms);//最初缺少这步，导致输出的房间信息为乱码
	do {
		printf("\t*欢迎光临本酒店*\t\n");
		printf("\t*很高兴为您服务*\t\n");
		printf("\t*1.工作人员*\t\n");
		printf("\t*2.游客登录*\t\n");
		printf("\t*0.退出*\t\n");
		printf("请做出选择:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				//调用函数要传递已定义好的变量，非类型声明
				hotel_system(room, &numRooms, guest, numGuest);
				//是numRooms变量的地址，这样可在函数内部修改值
				break;
			case 2:
				guest_system(guest, room, &numGuest, &numRooms);
				break;
			case 0:
				printf("感谢使用，再见！\n");
				break;
			default:
				printf("错误输入");
				system("pause");//暂停，按任意键继续
				system("cls");//清屏
		}
	} while (choice != 0);
	return 0;
}
