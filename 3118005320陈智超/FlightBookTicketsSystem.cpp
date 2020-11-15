#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define FALSE -1
#define TRUE 1


typedef int Status;
//��������ö���࣬����һ��������
enum Week {
    Mon = 1, Tues = 2, Wed = 3, Thurs = 4, Fri = 5, Sat = 6, Sun = 7
};
//�˿ͽڵ�
typedef struct CustomerNode {
    char name[10];//�ͻ�����
    int clientTickets;//�ͻ���Ʊ��
    char identification[20];//�ͻ����֤����
    int rank;//��λ�ȼ�
    CustomerNode *next;
} CustomerNode, *CusLinkList;

//�򲹶����еĽڵ�
typedef struct WaitPassenger {
    char name[10];//����
    char identification[20]; //���֤
    int preTickets;//Ԥ����Ʊ��
    struct WaitPassenger *next;
} WaitQNode, *PWait;

//�򲹶���
typedef struct Queue {
    PWait front;//�Ⱥ��油�ͻ��������ͷָ��
    PWait rear;//�Ⱥ��油�ͻ��������βָ��
} LinkQueue;

//��װ�˿͵������Ͷ�Ʊ�������֤
//���ں򲹿ͻ�����ʱ�ѹؼ��ַ��� 
typedef struct NameAndNumAndID {
    char name[10];//����
    char identification[20]; //���֤����
    int num;//��Ʊ��
} NameAndNumAndID;

//����ڵ�
typedef struct Flight {
    char startPoint[20];//���վ��
    char destination[20];//�յ�վ��
    char flightCodeID[20];//����ID���൱��������
    char planeNum[20];//�ɻ���
    char day[20];//�������ڣ����ڼ���
    int totalTickets;//��Ա����(��Ʊ��)
    int left;//����Ʊ��
    int leftEconomicTicket; //����Ʊʣ����
    int leftBusinessTicket; //����Ʊʣ����
    Flight *next;
    CusLinkList cusLinkList;//��Ա������ָ���Ա���������ͷָ��
    LinkQueue waitQueue1;//���òպ򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������
    LinkQueue waitQueue2;//����պ򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������

} Flight, FlightNode, *PFlight;


//�����ǽӿ�����
/**
 *�����Լ�����ĺ���ID��ѯ����ָ����ʽ����
 * @return  ����ָ��
 */
Flight *find();

/**
 * ��ʼ����ͷ����������
 * @param q
 */
Status InitQueue(LinkQueue &q);

/**
 * ��ʼ���Ѷ�Ʊ�˿�ָ������
 * @param cusLinkList �����г�Ա�����ͷָ��
 * @return
 */
Status InitCusLinkList(CusLinkList &cusLinkList);


/**
 * ��ӡinfo����Ļ�����Ϣ
 * @param info
 */
void Display(struct Flight *info);

/**
 * ���Ӻ���ʱ�������ڵĸ���������1��������һ��7���������գ�
 * @param day1 ��������1-7�е�һ��
 * @param day ��������������Է��ػ�ȥ����������ڱ���
 * @return ���ز���״̬�������Ƿ�Ϸ�
 */
Status IputDay(int day1, char day[]);

/**
 *���ݿͻ�������յ�վ�����������Ϣ
 */
void SearchFlight();

/**
 * ��ӡ��Ʊ��Ա������Ŀͻ�������Ϣ(���������֤)
 */
void PriCusInfo();

/**
 * ��Ʊ����ģ��
 */
void BookTickets();

/**
 * ��Ʊ����ģ��
 */
void ReturnTicket();

/**
 * ��������
 */
void SearchFace();

/**
 * ��Ʊ����
 * ���ڶ�Ʊģ��
 */
void BookticketFace();

/**
 * ��Ʊģ�����
 */
void ReturnTicketsFace();

/**
 * �˳�����ģ��
 */
void GoodbyeFace();

/**
 * ��ѯģ��
 * ��ӡȫ��������Ϣ
 * @param flight ������Ǻ��������ͷָ��
 */
void PrintFilghtlist(Flight *flight);

/**
 *�˵����溯��
 * @return ����ѡ��Ĳ���
 */
int MenuSelect();

/**
 * ����Ա����
 */
void AdministratorFace();

/**
 *���ݿͻ��������㣬�յ�վ�����������Ϣ
 */
void SearchFlight();

/**
 * �Ƽ���Ʊ
 * @param startPoint ���
 * @param destination �յ�
 * @param flight ԭ���࣬��������ѡ��ͬһ·�ߵ���ͬ����ID�ĺ���
 */
void Suggest(char startPoint[], char destination[], Flight *flight);

/**
 * ��flight1��4��������ͷ���뷨���뵽pFlight��������
 * @param flight1 �������������������
 * @return ���ز����Ƿ�ɹ�
 */
Status Create(PFlight flight1);

/**
 * �Ƽ�ͬһ·�ߵ���������
 * @param destination
 * @param pflight ԭ���࣬�����жϺ����ѵ��ĺ����Ƿ�һ��
 * @return �Ҳ����ͷ���FALSE�����򷵻�TRUE
 */
Status RecommendFlight(char startPoint[], char destination[], Flight *pflight);

/**
 * ����Ա���뺽��ʱ�������࣬��ֹ����ID�ظ�������ID�൱��������
 * @param flight
 * @param flightCodeID
 * @return  �����Ƿ��ظ�
 */
Status TraverseFlight(Flight *flight, char flightCodeID[]);



//�ӿڴ���ʵ��

//����ȫ��ָ�����pFlight�����������ͷָ��
Flight *pFlight;

//������������
Flight flight1[6] = {
        {"����", "����", "1", "B3333", "����һ", 10, 10, 5},
        {"����", "����", "2", "D5555", "���ڶ�", 8,  8,  4},
        {"����", "����", "3", "L6666", "������", 10, 10, 5},
        {"�Ϻ�", "����", "4", "K9999", "������", 8,  8,  4},
        {"����", "�ɶ�", "5", "K7777", "������", 10, 10, 5},
        {"�ɶ�", "����", "6", "K8888", "������", 8,  8,  4}
};

/**
 * ��ʼ����������
 * Ŀ����Ҫ��ʼ����pFlightΪͷ���Ŀպ�������,¼�뺽����Ϣ�����Ӻ���󽫺�������������
 */
void InitFlight() {
    pFlight = (Flight *) malloc(sizeof(Flight));//����ͷ���Ŀռ�
    if (pFlight == NULL) exit(0);
    pFlight->next = NULL;//��ͷ���h��ָ������Ϊ��
}

/**
 * ��flight1��4��������ͷ���뷨���뵽pFlight��������
 * @param flight1 �������������������
 * @return ���ز����Ƿ�ɹ�
 */
Status Create(PFlight flight1) {
    Flight *p = pFlight, *q;
    for (int i; i < 6; i++) {
        q = (Flight *) malloc(sizeof(Flight));
        if (q == NULL)
            return ERROR;
        strcpy(q->startPoint, flight1[i].startPoint);
        strcpy(q->destination, flight1[i].destination);
        strcpy(q->flightCodeID, flight1[i].flightCodeID);
        strcpy(q->planeNum, flight1[i].planeNum);
        strcpy(q->day, flight1[i].day);
        q->totalTickets = flight1[i].totalTickets;
        q->left = flight1[i].totalTickets;
        q->leftEconomicTicket = flight1[i].leftEconomicTicket;
        q->leftBusinessTicket = flight1[i].totalTickets - flight1[i].leftEconomicTicket;
        //��ʼ���˿�����
        InitCusLinkList(q->cusLinkList);
        //q->cusLinkList = (CustomerNode *) malloc(sizeof(CustomerNode));
        //q->cusLinkList->next = NULL;
        InitQueue(q->waitQueue1);
        InitQueue(q->waitQueue2);

        q->next = p->next;
        p->next = q;

    }
    return OK;

}


/**
  * ����Ա����
  * ���µĺ�������뵽���������У�
  * ����ͷ���뷨
  * @return ���ز����Ƿ�ɹ�
  */
Status InsertFlight() {
    FlightNode *q;//����qΪ�����ӵĺ������ָ����β�
    Flight *p = pFlight;
    int mark = 1;

    while (mark != 0) {
        q = (FlightNode *) malloc(sizeof(FlightNode));
        if (q == NULL)
            return ERROR;

        printf("\t\t������������������\n");
        printf("\t\t�����뺽��ID\n");
        scanf("%s", q->flightCodeID);
        Status status = TraverseFlight(pFlight, q->flightCodeID);
        if (status == ERROR) {
            printf("�ú���ID�Ѿ����ڣ����������뺽��ID\n");
            continue;
        }
        printf("\t\t���������վ��\n");
        scanf("%s", q->startPoint);
        printf("\t\t�������յ�վ��\n");
        scanf("%s", q->destination);
        printf("\t\t������ɻ���\n");
        scanf("%s", q->planeNum);
        printf("\t\t�������������(1��������,2�������ڶ�.....7����������)\n");
        int day1;
        scanf("%d", &day1);
        while (ERROR == IputDay(day1, q->day)) {
            printf("������Ϸ�����(1-7)\n");
            scanf("%d", &day1);
        };

        printf("\t\t������˿Ͷ���\n");
        scanf("%d", &q->totalTickets);
        q->left = q->totalTickets;

        printf("\t\t�����뾭��Ʊ��Ŀ��ͬʱҲ����������Ʊ����Ŀ��\n");
        scanf("%d", &q->leftEconomicTicket);
        //����Ʊ��Ŀ = ��Ʊ��Ŀ - ����Ʊ��Ŀ
        q->leftBusinessTicket = q->totalTickets - q->leftEconomicTicket;
        InitCusLinkList(q->cusLinkList);
        //��ʼ��
        InitQueue(q->waitQueue1);
        InitQueue(q->waitQueue2);

        q->next = p->next;
        p->next = q;

        printf("\t\t�Ƿ����¼�뺽����Ϣ���������ּ�����0��ʾֹͣ����\n");
        printf("\t\t�����룺");
        scanf("%d", &mark);
    }
    return OK;
}

/**
  * ����Ա����
  * ɾ���ڵ�
  * @return ���ز����Ƿ�ɹ�
  */
Status DeleteFlight() {
    char flightCodeID[20];
    printf("�����뺽��ID\n");
    scanf("%s", flightCodeID);
    PFlight pre = pFlight;
    PFlight p = pre->next;

    while (p != NULL) {
        if (!strcmp(flightCodeID, p->flightCodeID)) {
            pre->next = p->next;
            free(p);
            return OK;
        }
        pre = p;
        p = p->next;
    }
    return ERROR;

}

/**
 * ��֤����Ա����
 * @return ���ز������
 */
Status AdministratorVerify() {
    char pwd[20] = "admin";//����Ա����
    char password[20];//���������룬������֤
    printf("���������Ա����:\n");
    scanf("%s", password);
    if (strcmp(pwd, password)) {
        printf("�����������������:\n");
        return FALSE;
    }
    printf("��֤�ɹ�\n");
    return TRUE;
}
/**
 * ����Ա�Ĳ�ѯ����
 * ��ӡ��Ʊ��Ա������Ŀͻ�������Ϣ(���������֤)
 */
void AdminPriCusInfo() {
    CusLinkList p;
    Flight *info;
    info = find();
    if (info == NULL) {
        printf("û���������\n");
        return;
    }
    //ͷ������һ���ڵ㿪ʼ����
    p = info->cusLinkList->next;
    if (p != NULL) {
        printf("�ͻ�����   ��Ʊ����   ��λ�ȼ���1���òգ�2����գ�    ���֤����\n");
        while (p) {
            printf("%s\t\t%d\t\t%d\t\t\t%s\n", p->name, p->clientTickets, p->rank, p->identification);
            p = p->next;
        }
    } else
        printf("�ú���û�пͻ���Ϣ!!\n");
}

/**
 * ����Աģ��
 * ����Ա���溯��
 */
void AdministratorFace() {
    int a2;
    int loop2;//goto���
    loop2:
    {
        //system("cls");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");


        printf("                          Welcome To ����Աģ��\n");
        printf("                ------------------------------------\n");
        printf("                |           1.������Ϣ              |\n");
        printf("                |           2.�ͻ���Ϣ              |\n");
        printf("                |           3.���Ӻ���              |\n");
        printf("                |           4.ɾ������              |\n");
        printf("                |           5.������һ��            |\n");
        printf("                ------------------------------------|\n");
        printf("                 ����������ѡ��:");
        scanf("%d", &a2);
    }
    switch (a2) {
        case 1:
            PrintFilghtlist(pFlight);
            system("PAUSE");
            AdministratorFace();
            break;
        case 2:
            AdminPriCusInfo();
            AdministratorFace();
        case 3:
            InsertFlight();
            AdministratorFace();
            break;
        case 4:
            if (OK == DeleteFlight()) {
                printf("ɾ���ɹ�\n");
            } else {
                printf("û��������࣬ɾ��ʧ�ܣ�\n");
            };
            AdministratorFace();
        case 5:
            MenuSelect();
            break;
        default:
            goto loop2;
    }
}


/**
 * ���Ӻ���ʱ�������ڵĸ���������1��������һ��7���������գ�
 * @param day1 ��������1-7�е�һ��
 * @param day ��������������Է��ػ�ȥ����������ڱ���
 * @return ���ز���״̬�������Ƿ�Ϸ�
 */
Status IputDay(int day1, char day[]) {
    switch (day1) {
        case Mon:
            strcpy(day, "����һ");
            break;
        case Tues:
            strcpy(day, "���ڶ�");
            break;
        case Wed:
            strcpy(day, "������");
            break;
        case Thurs:
            strcpy(day, "������");
            break;
        case Fri:
            strcpy(day, "������");
            break;
        case Sat:
            strcpy(day, "������");
            break;
        case Sun:
            strcpy(day, "������");
            break;
        default:
            return ERROR;
    }
    return OK;
}


/**
 *�˵����溯��
 * @return ����ѡ��Ĳ���
 */
int MenuSelect() {
    int select;
    Status status;
    flag:
    {
        system("cls");
        printf("\n");
        printf("                         18�����繤��4����ǳ�  3118005320\n");
        printf("                               ָ����ʦ��������            ");
        printf("\n");
        printf("�������������������������������������������������\n");
        printf("�������������������������������������������������\n");
        printf("������������������������������������������������������\n");
        printf("��������������������������������������������������������\n");
        printf("���������������������������������������������������������\n");
        printf("��������������������������������������������������������������\n");
        printf("�������������������������������������������������������������������������\n");
        printf("��������������������������������������������������������������������������\n");
        printf("���������������������������������������������������������������������\n");
        printf("�����������������������������������������������������������������\n");
        printf("������������������������������������������������������������������\n");
        printf("�����������������������������������������������������������������\n");
        printf("������������������������������������������������������������������\n");
        printf("�����������������������������������������������������������������������\n");
        printf("���������������������������������������������������������������������\n");
        printf("�����������������������������������������������������������\n");
        printf("����������������������������������������������������������\n");
        printf("���������������������������������������������������������\n");
        printf("�����������������������������������������������������������\n");
        printf("������������������������������������������������������������������������\n");
        printf("������������������������������������������������������������������������������\n");
        printf("����������������������������������������������������������\n");
        printf("��������������������������������������������������\n");
        printf("�������������������������������������������������\n");
        printf("\n");
        printf("\n");
        printf("                               ��ӭ�������ն�Ʊϵͳ\n");
        printf("                        ------------------------------------\n");
        printf("                        |          1.  ��ѯģ��             |\n");
        printf("                        |          2.  ����ģ��             |\n");
        printf("                        |          3.  ��Ʊģ��             |\n");
        printf("                        |          4.  ��Ʊģ��             |\n");
        printf("                        |          5.  ����Աģ��           |\n");
        printf("                        |          6.  �뿪ϵͳ             |\n");
        printf("                        ------------------------------------\n");
        printf("                        �����루1-5��������Ч�� ����������ѡ��:");
        scanf("%d", &select);


    }
    switch (select) {
        case 1:
            //��ѯ���к�����Ϣ
            //���뺽������ͷָ�룬��ӡ�����к�����Ϣ
            PrintFilghtlist(pFlight);
            system("PAUSE");
            MenuSelect();
            break;
        case 2:
            //��������ģ��
            SearchFace();
            system("PAUSE");
            MenuSelect();
            break;
        case 3:
            //���붩Ʊģ��
            BookticketFace();
            system("PAUSE");
            MenuSelect();
            break;
        case 4:
            //������Ʊģ��
            ReturnTicketsFace();
            system("PAUSE");
            MenuSelect();
            break;
        case 5:
            //�������Աģ��
            while (1) {
                status = AdministratorVerify();
                if (TRUE == status)
                    break;
            }
            AdministratorFace();
            system("PAUSE");
            MenuSelect();
            break;
        case 6:
            //�˳�ģ��
            GoodbyeFace();
            break;
        default:
            goto flag;
    }

}

/**
 * ��ӡinfo����Ļ�����Ϣ
 * @param info
 */
void Display(Flight *info) {
    printf("%8s\t%8s\t%3s\t%s\t%4s\t\t%3d\t%10d\t%10d\t%10d\n", info->startPoint, info->destination, info->flightCodeID,
           info->planeNum, info->day,
           info->totalTickets, info->left, info->leftEconomicTicket, info->leftBusinessTicket);
}


/**
 * ��ѯģ��
 * ��ӡȫ��������Ϣ
 * @param flight ������Ǻ��������ͷָ��
 */
void PrintFilghtlist(Flight *pflight) {
    Flight *p;
    //��ͷ����ͷָ�룬���Դ���һ��ָ�뻹�Ǳ���
    p = pflight->next;
    system("cls");
    printf("���վ��\t�յ�վ��\t����ID\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");
    while (p != NULL) {
        //����Display������ӡ��ÿ������ڵ����Ϣ
        Display(p);
        p = p->next;
    }
    printf("\n\n");
}


/**
 *���ݿͻ��������㣬�յ�վ�����������Ϣ
 */
void SearchFlight() {
    char startPonit[10];
    char destination[10];
    int flag = 0;
    system("cls");
    printf("���������վ��:");
    scanf("%s", startPonit);
    printf("�������յ�վ��:");
    scanf("%s", destination);
    struct Flight *p;
    p = pFlight->next;
    printf("���վ��\t�յ�վ��\t����ID\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");

    while (p != NULL) {
        if ((strcmp(startPonit, p->startPoint) == 0) && (strcmp(destination, p->destination) == 0) ) {
            flag = 1;
            Display(p);
        }
        p = p->next;
    }


    printf("\n\n");

    if (flag == 0)
        printf("�Բ��𣬸ú���δ�ҵ�! \n");

}

/**
 * �Ƽ�ͬһ·�ߵ���������
 * @param destination
 * @param pflight ԭ���࣬�����жϺ����ѵ��ĺ����Ƿ�һ��
 * @return �Ҳ����ͷ���FALSE�����򷵻�TRUE
 */
Status RecommendFlight(char startPoint[], char destination[], Flight *pflight) {
    //��Ǳ������Ƿ��ҵ�ͬһ·�ߵĺ���
    int flag = 0;
    system("cls");
    struct Flight *p;
    p = pFlight->next;
    printf("Ѱ��ͬһ·�ߵĺ���\n");
    printf("���վ��\t�յ�վ��\t����ID\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");

    while (p != NULL) {
        //·����ͬ���Ҳ���ͬһ�����࣬���flag = 1����ʾ�ҵ�
        if (strcmp(destination, p->destination) == 0 && strcmp(startPoint, p->startPoint) == 0 && p != pflight) {
            flag = 1;
            Display(p);
        }
        p = p->next;

    }
    printf("\n\n");

    //û����ͬ·�ߵĺ���
    if (flag == 0)
        return FALSE;
    return TRUE;
}


/**
 * ���p�ڵ�ĺ�����Ϣ
 * @param p ����ڵ�
 */
void FlightInfo(Flight *p) {
    printf("���վ��\t�յ�վ��\t����ID\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ��\t����Ʊʣ��\n");
    Display(p);
    printf("\n\n");

}


/**
 * ����Ա���뺽��ʱ�������࣬��ֹ����ID�ظ�������ID�൱��������
 * @param flight
 * @param flightCodeID
 * @return  �����Ƿ��ظ�
 */
Status TraverseFlight(Flight *flight, char flightCodeID[]) {
    Flight *p = flight;
    while (p != NULL) {
        //���к���ID�ظ�ʱ�򣬷���ERROR��
        if (!strcmp(flightCodeID, p->flightCodeID)) {
            return ERROR;
        }

        p = p->next;
    }
    //����ĺ���ID���ظ�
    return OK;

}


/**
 *�����Լ�����ĺ���ID��ѯ����ָ����ʽ����
 * @return  ����ָ��
 */
Flight *find() {
    char number[10];
    int i = 0;
    int loop;

    printf("�����뺽��ID: ");
    scanf("%s", number);

    //ͷ������һ���ڵ㿪ʼ����
    Flight *p = pFlight->next;

    while (p != NULL) {
        if (!strcmp(number, p->flightCodeID))
            return p;

        p = p->next;
    }
    return NULL;
}

/**
 * ��ӡ��Ʊ��Ա������Ŀͻ�������Ϣ(���������֤)
 */
void PriCusInfo() {
    CusLinkList p;
    Flight *info;
    info = find();
    if (info == NULL) {
        printf("û���������\n");
        return;
    }
    //ͷ������һ���ڵ㿪ʼ����
    p = info->cusLinkList->next;
    if (p != NULL) {
        printf("�ͻ�����   ��Ʊ����   ��λ�ȼ���1���òգ�2����գ�\n");
        while (p) {
            printf("%s\t\t%d\t%d\n", p->name, p->clientTickets, p->rank);
            p = p->next;
        }
    } else
        printf("�ú���û�пͻ���Ϣ!!\n");
}

/**
 * ��Ʊ�ɹ�֮�󣬽��˿���Ϣ���뵽��Ӧ����Ķ���Ա�������У�����
 * @param head �˿�������ͷָ��
 * @param amount �ó˿Ͷ�Ʊ������
 * @param name �˿͵�����
 * @param rank ��Ʊ�ĵȼ�
 * @return  �˿�����ͷָ��
 */
CusLinkList insertlink(CusLinkList &head, int amount, char name[], char identification[], int rank) {
    //��Ա�������½ڵ�new1
    CusLinkList new1;
    new1 = (CustomerNode *) malloc(sizeof(CustomerNode));
    if (new1 == NULL) {
        printf("\n�ڴ治��\n");
        return NULL;
    }
    //������˿���Ϣ��ֵ��new1�ڵ�
    strcpy(new1->name, name);
    strcpy(new1->identification, identification);
    new1->clientTickets = amount;
    new1->rank = rank;

    //ͷ���뷨�����Ա������
    new1->next = head->next;
    head->next = new1;
    // head = new1;
    // new1->next =
    return head;
}

/**
 * ��ʼ���Ѷ�Ʊ�˿�ָ������
 * @param cusLinkList �����г�Ա�����ͷָ��
 * @return
 */
Status InitCusLinkList(CusLinkList &cusLinkList) {
    CusLinkList q = cusLinkList;
    cusLinkList = (CustomerNode *) malloc(sizeof(CustomerNode));
    cusLinkList->next = NULL;
}

/**
 * ��ʼ����ͷ����������
 * @param q
 */
Status InitQueue(LinkQueue &q) {
    WaitQNode *p;
    p = (WaitQNode *) malloc(sizeof(WaitQNode));
    if (p == NULL) {
        printf("�ڴ治��\n");
        return ERROR;
    }

    p->next = NULL;
    q.front = q.rear = p;
    return OK;

}

/**
 *��ӣ������ŶӵȺ�Ŀͻ�������
 * @param q ��ͷ����������
 * @param name
 * @param amount
 * @return
 */
LinkQueue Appendqueue(LinkQueue &q, char name[], int amount, char identification[]) {
    PWait new1;
    new1 = (PWait) malloc(sizeof(WaitQNode));
    strcpy(new1->name, name);
    strcpy(new1->identification, identification);
    new1->preTickets = amount;
    new1->next = NULL;

    q.rear->next = new1;
    q.rear = new1;

    return q;
}

/**
 * ���Ӻ���
 * @param Q   QΪ�򲹶�Ʊ�ͻ��Ķ���
 * @param NameAndNumAndIDAndID �򲹿ͻ��������Ͷ�Ʊ��Ŀ������ʱ���������͹ؼ��ֺ����֤����
 * @return
 */
Status QueueDelete(LinkQueue &q, NameAndNumAndID &NameAndNumAndID) {
    WaitQNode *p;
    p = q.front->next;
    //��ͷ����������frontָ���rearָ�����ʱ���൱�ڶ���Ϊ�գ�û��Ԫ�س���
    if (q.front == q.rear) {
        return ERROR;
    }
    //����
    q.front->next = p->next;
    //���ӵ���ʱ��rear = front
    if (q.front->next == NULL) {
        q.rear = q.front;
    }

    //���س���Ԫ�صĹؼ���Ϣ�������򲹿ͻ��������Ͷ�Ʊ��
    NameAndNumAndID.num = p->preTickets;
    strcpy(NameAndNumAndID.name, p->name);
    strcpy(NameAndNumAndID.identification, p->identification);
    free(p);

    return OK;
}

/**
 * ��Ʊģ��
 */
void BookTickets() {
    struct Flight *info;
    int amount, rank;
    int tickets;//ʣ�������Ʊ��Ŀ���߾���Ʊ��Ŀ
    char name[10];
    char identification[20];
    system("cls");
    //���ò��Һ��ຯ�������ظ�
    int loop1;
    loop1:
    {
        info = find();
    };

    if (info == NULL){
        printf("û���������, ����������\n");
        goto loop1;
    }


    int loop2;
    loop2:
    {  printf("����ȷ�����㶩Ʊ����Ҫ������:");
        scanf("%d", &amount);
    };
    //�Ƿ��ַ�����������
    if (amount <= 0 ) {
        goto loop2;
    }
    
    printf("����ȷ��������Ʊ�Ĳ�λ�ȼ���1�����òգ�2��������������գ�:");
    scanf("%d", &rank);
    if (rank == 1)
        tickets = info->leftEconomicTicket;
    else
        tickets = info->leftBusinessTicket;

    if (amount <= tickets) {
        int i;
        printf("��������������:");
        scanf("%s", name);
        printf("�������������֤����:");
        scanf("%s", identification);
        CusLinkList head = info->cusLinkList;
        //��Ʊ�ɹ��������Ա��������
        insertlink(head, amount, name, identification, rank);
        for (i = 0; i < amount; i++)
            printf("%s ����λ����: %d\n", name, info->totalTickets - info->left + i + 1);
        info->left -= amount;

        if (rank == 1)
            info->leftEconomicTicket -= amount;
        else
            info->leftBusinessTicket -= amount;

        printf("\nף����;��죡��ӭ�ٴι���\n");
    } else
        loop0:
        {
            char r;
            printf("�õȼ���Ʊ���㣬��Ʊʧ�ܣ�����Ϊ�ú���˿���Ϣ,ϣ�������Ķ�Ʊ��������\n");
            FlightInfo(info);
            printf("�Ƿ�ı䶩Ʊ�ƻ���Y/N\n");
            r = getch();
            printf("%c", r);
            if (r == 'Y' || r == 'y') {//�ı�ƻ�������ѡ�񺽰�
                BookTickets();
            } else {
                printf("\n�Ѿ�û�и����Ʊ������Ҫ�ŶӵȺ���?(Y/N)");
                r = getch();
                printf("%c", r);
                if (r == 'Y' || r == 'y') {//���ı�ƻ����ŶӺ�Ʊ
                    printf("\n�����������������ŶӶ�Ʊ�ͻ���:");
                    scanf("%s", name);
                    printf("\n�������������֤���ŶӶ�Ʊ�ͻ���:");
                    scanf("%s", identification);
                    if (rank == 1) {//���뾭�ò��ŶӶ���
                        info->waitQueue1 = Appendqueue(info->waitQueue1, name, amount, identification);
                    } else {//����������ŶӶ���
                        info->waitQueue2 = Appendqueue(info->waitQueue2, name, amount, identification);
                    }

                    printf("\n�Ŷӳɹ�!\n");
                } else {//���Ŷӣ�ѡ��ϵͳ�ṩ���������鷽��
                    printf("\n�Ƿ���ݽ��鶩Ʊ�����ǣ����Ƽ���ͬ�������յ�ĺ���Y/N");
                    r = getch();
                    printf("%c", r);
                    printf("%c", r);
                    if (r == 'Y' || r == 'y') {
                        //�����Ƽ�����
                        Suggest(info->startPoint, info->destination, info);
                    } else
                        printf("\n��ӭ���´��ٴζ�����\n");
                }
            }
        }

}



/**
 * �Ƽ���Ʊ
 * @param startPoint ���
 * @param destination �յ�
 * @param flight ԭ���࣬��������ѡ��ͬһ·�ߵ���ͬ����ID�ĺ���
 */
void Suggest(char startPoint[], char destination[], Flight *flight) {
    //struct Flight *info;
    //char name[10];
    //int amount, rank;
    //int i = 0, loop = 0;
    //info = pFlight;
    Status status = RecommendFlight(startPoint, destination, flight);
    if (status == FALSE)
        printf("�Բ���û����ͬ�����յ�ĺ�����");
    else {
        printf("�Ƿ���϶�ƱҪ��Y|N");
        {
            char r;
            r = getch();
            printf("%c", r);
            if (r == 'Y' || r == 'y') {
                BookTickets();
                system("PAUSE");
            } else
                printf("�����ݽ�����ж�Ʊ�����ڽ��˻����˵�");
            system("PAUSE");
            MenuSelect();
        }
    }


}

/**
 * ��Ʊ����ģ��
 */
void ReturnTicket() {
    struct Flight *info;
    int rank;
    //p1Ϊ����ָ�룬p2Ϊ����ָ�룬ָ��p1��ǰ��
    CustomerNode *p1, *p2, *head;
    //�ͻ�����
    char cusname[10];
    //�ͻ����֤
    char identification[20];
    system("cls");
    //infoָ�룬find�������ݺ���ID���ظú���ڵ��ָ��
    int loop;
    loop:
    {
        info = find();
    };

    if (info == NULL){
        printf("û���������, ����������\n");
        goto loop;
    }

    //headΪ�ú���ĵĳ�Ա�������ͷָ��
    head = info->cusLinkList;
    //��ͷ����ָ�룬head->next ��ʼ����
    p1 = head->next;
    printf("�������������: ");
    scanf("%s", cusname);
    printf("������������֤����: ");
    scanf("%s", identification);
    //���ݿͻ����������ͻ��Ƿ�Ʊ
    p2 = head;
    while (p1 != NULL) {
        if ((strcmp(cusname, p1->name) == 0) && (strcmp(identification, p1->identification) == 0)) break;
        p2 = p1;
        p1 = p1->next;
    }

    if (p1 == NULL) {
        printf("�Բ�����û�ж���Ʊ�����������֤����Ӧ\n");
        return;
    } else {//��Ʊ�ɹ�
        //�ӳ˿����������Ƴ��ýڵ�
        rank = p1->rank;
        p2->next = p1->next;
        //�ӻظú����ʣ��Ʊ
        info->left += p1->clientTickets;
        if (rank == 1) {
            info->leftEconomicTicket += p1->clientTickets;
        } else {
            info->leftBusinessTicket += p1->clientTickets;
        }
        printf("%s  �ɹ���Ʊ��\n", p1->name);
        free(p1);
    }

    LinkQueue queue1 = info->waitQueue1;
    LinkQueue queue2 = info->waitQueue2;
    NameAndNumAndID nameAndNumAndID = {0, 0};


    if (rank == 1) { //�о��ò���Ʊ��ѯ�ʾ��ò��ŶӵĿͻ�
        for (; queue1.front->next != NULL && queue1.front->next->preTickets <= info->leftEconomicTicket;) {
            //�Ӻ򲹿ͻ������У����ӿͻ��������Ͷ�Ʊ����NameAndNumAndID����
            QueueDelete(info->waitQueue1, nameAndNumAndID);
            int y;
            printf("�� ���ò�Ʊ ʣ�� , �𾴵�%s ��\n", nameAndNumAndID.name);
            printf("�Ƿ�ȷ�϶�Ʊ��1ȷ�϶�Ʊ�� �������־ܾ���Ʊ\n");
            scanf("%d", &y);

            if (y == 1) {
                //�ŶӶ�Ʊ�ɹ�
                for (int i = 0; i < nameAndNumAndID.num; i++)
                    printf("�ŶӶ�Ʊ�ɹ�  %s ����λ����:%d\n", nameAndNumAndID.name, (info->left) - i);
                //ʣ��Ʊ����
                info->left -= nameAndNumAndID.num;
                info->leftEconomicTicket -= nameAndNumAndID.num;
                //��Ա������������ŶӶ�Ʊ�ɹ��Ŀͻ�
                info->cusLinkList = insertlink(info->cusLinkList, nameAndNumAndID.num, nameAndNumAndID.name,
                                               nameAndNumAndID.identification, rank);
            }
        }
    } else { //������տͻ���Ʊ��ѯ��������ŶӵĿͻ�
        for (; queue2.front->next != NULL && queue2.front->next->preTickets <= info->leftBusinessTicket;) {
            //�Ӻ򲹿ͻ������У����ӿͻ��������Ͷ�Ʊ����NameAndNumAndID����
            QueueDelete(info->waitQueue2, nameAndNumAndID);
            int y;
            printf("�� �����Ʊ ʣ�� , �𾴵�%s ��\n", nameAndNumAndID.name);
            printf("�Ƿ�ȷ�϶�Ʊ��1ȷ�϶�Ʊ�� �������־ܾ���Ʊ\n");
            scanf("%d", &y);

            if (y == 1) {
                //�ŶӶ�Ʊ�ɹ�
                for (int i = 0; i < nameAndNumAndID.num; i++)
                    printf("�ŶӶ�Ʊ�ɹ�  %s ����λ����:%d\n", nameAndNumAndID.name, (info->left) - i);
                //ʣ��Ʊ����
                info->left -= nameAndNumAndID.num;
                info->leftBusinessTicket -= nameAndNumAndID.num;
                //��Ա������������ŶӶ�Ʊ�ɹ��Ŀͻ�
                info->cusLinkList = insertlink(info->cusLinkList, nameAndNumAndID.num, nameAndNumAndID.name,
                                               nameAndNumAndID.identification, rank);
            }
        }

    }


}

/**
 * ��������
 */
void SearchFace() {
    int a2;
    int loop2;//goto���
    loop2:
    {
        system("cls");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");


        printf("                  Welcome To ����ģ��\n");
        printf("        ------------------------------------\n");
        printf("        |           1.����������Ϣ           | \n");
        printf("        |           2.������һ��˵�         | \n");
        printf("        ------------------------------------|\n");
        printf("                 ����������ѡ��:");
        scanf("%d", &a2);
    }
    switch (a2) {
        case 1:
            SearchFlight();
            system("PAUSE");
            SearchFace();
            break;
        case 2:
            MenuSelect();
            break;
        default:
            goto loop2;
    }
}

/**
 * ��Ʊ����
 * ���ڶ�Ʊģ��
 */
void BookticketFace() {
    int a3;
    int loop3;
    loop3:
    {
        system("cls");
        printf("\n");
        printf("\n");
        printf("             Welcome To ��Ʊģ��\n");
        printf("       -----------------------------------------------\n");
        printf("       |           1.�ͻ���Ʊ                          |\n");
        printf("       |           2.���������յ���������             |\n");
        printf("       |           3.��ѯ���к���                       |\n");
        printf("       |           4.ͨ������ID��ѯ��Ʊ�ͻ�����         |\n");
        printf("       |           5.������һ���˵�                    |\n");
        printf("       ------------------------------------------------\n");
        printf("                 ����������ѡ��:");
        scanf("%d", &a3);
    }
    switch (a3) {
        case 1:
            //��Ʊ
            BookTickets();
            system("PAUSE");
            BookticketFace();
            break;
        case 2:
            //���������յ��ѯ
            SearchFlight();
            system("PAUSE");
            BookticketFace();
            break;
        case 3:
            PrintFilghtlist(pFlight);
            system("PAUSE");
            BookticketFace();
            break;
        case 4:
            //Ϊ�˱��ܣ�ֻ�ܲ鵽�ͻ��������Ͷ�Ʊ�����鲻�����֤
            PriCusInfo();
            system("PAUSE");
            BookticketFace();
            break;
        case 5:
            MenuSelect();
            break;
        default:
            goto loop3;
    }
}

/**
 * ��Ʊģ�����
 */
void ReturnTicketsFace() {
    int a3;
    int loop4;
    loop4:
    {
        system("cls");
        printf("\n");
        printf("\n");
        printf("               Welcome To ��Ʊģ��\n");
        printf("    -------------------------------------\n");
        printf("    |           1.������Ʊ����            |\n");
        printf("    |           2.������һ���˵�          |\n");
        printf("    --------------------------------------\n");
        printf("                            ����������ѡ��:");
        scanf("%d", &a3);
    }
    switch (a3) {
        case 1:
            ReturnTicket();
            system("PAUSE");
            ReturnTicketsFace();
            break;
        case 2:
            MenuSelect();
            break;
        default:
            goto loop4;
    }
}

/**
 * �˳�����ģ��
 */
void GoodbyeFace() {
    system("cls");
    printf("\n");
    printf("\n");


    printf("�������������������������������������������������\n");
    printf("�������������������������������������������������\n");
    printf("������������������������������������������������������\n");
    printf("��������������������������������������������������������\n");
    printf("���������������������������������������������������������\n");
    printf("��������������������������������������������������������������\n");
    printf("�������������������������������������������������������������������������\n");
    printf("��������������������������������������������������������������������������\n");
    printf("���������������������������������������������������������������������\n");
    printf("�����������������������������������������������������������������\n");
    printf("������������������������������������������������������������������\n");
    printf("�����������������������������������������������������������������\n");
    printf("������������������������������������������������������������������\n");
    printf("�����������������������������������������������������������������������\n");
    printf("���������������������������������������������������������������������\n");
    printf("�����������������������������������������������������������\n");
    printf("����������������������������������������������������������\n");
    printf("���������������������������������������������������������\n");
    printf("�����������������������������������������������������������\n");
    printf("������������������������������������������������������������������������\n");
    printf("������������������������������������������������������������������������������\n");
    printf("����������������������������������������������������������\n");
    printf("��������������������������������������������������\n");
    printf("�������������������������������������������������\n");
    printf("\n");
    printf("\n");
    printf("             ---------------------------------------------\n");
    printf("             |            ��лʹ�ú��պ��ඩƱϵͳ        |\n");
    printf("             |                                           |\n");
    printf("             |                    GoodBye��               \n");
    printf("             --------------------------------------------\n");

}

/**
 * pFlightΪȫ�ֱ��������������ͷָ��
 * �ȳ�ʼ��pFlight���������ٰ�flight1���ĸ���Ӱ����ݲ���pFlight����
 * ���ò˵�����
 */
int main() {
    //��ʼ��pFlight��pFlightΪȫ�ֱ�����
    InitFlight();
    //��flight1�е����ݴ�����ʼ�����������溬���ĸ��ڵ�
    Create(flight1);
    //�˵�����
    MenuSelect();
    return 0;
}


