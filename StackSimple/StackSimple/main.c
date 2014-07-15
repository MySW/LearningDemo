//
//  main.c
//  StackSimple
//
//  Created by 钱钱 on 14-7-15.
//  Copyright (c) 2014年 QGM. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _p{
    // 做在圈内的位置
    int     index;
    // 要喊的数字
    int     speak;
    // 姓名
    char    name;
    // 当前人位置的下一个人
    struct _p *next;
    // 当前人位置的上一个人
    struct _p *pre;
}Person;

// 生成一个人的函数
// 通过在圈内的位置和人的名字得到一个人
Person *initPerson (int index, char c);
Person *initPerson (int index, char c)
{
    Person *p = (Person *)malloc(sizeof(Person));
    p ->name  = c;
    p ->index = index;
    p ->speak = 0;
    return p;
}

// 连接一个人
void connectPerson(Person *left, Person *right);
void connectPerson(Person *left, Person *right)
{
    left -> next = right;
    right -> pre = left;
}

// 删除一个人的函数
void deletePerson(Person *person);
void deletePerson(Person *person)
{
    printf("%c在圈内第%d个位置走出了圈外\n", person->name, person->index);
    // 为了程序内的逻辑正确，修改删除的人的前一个额人的喊的值为默认值
    person -> pre -> speak = 0;
    connectPerson(person ->pre, person ->next);
    free(person);
}

// 检查一个人喊的数是否正确
// value 默认为3........
void checkPerson(Person *person, int value);
void checkPerson(Person *person, int value)
{
    if (person -> speak == value) {
        deletePerson(person);
    }
}

// 设置一个人将要喊的数
void setPersonSpeack(Person *person);
void setPersonSpeack(Person *person)
{
    Person *pre = person ->pre;
    if (pre->speak == 0) {
        person ->speak = 1;
    }
    else
    {
        person -> speak = pre -> speak + 1;
    }
}

// 初始化游戏
// count 代表人的个数
// value喊到几就出去的人
Person * initGame(int count, int value);
Person * initGame(int count, int value)
{
    // 这是一个人，不能动
    Person *headPerson = initPerson(0, 'a');
    
    // 中间变量
    Person *temPerson = headPerson;
    for (int i = 1; i < count - 1; i ++) {
        Person *person = initPerson(i, 'a' + i);
        
        // 将中间变量和per连起来
        connectPerson(temPerson, person);
        
        // 将中间变量往下移动
        temPerson = person;
        
    }
    // 将最后一个人tempPerson和headPerson连接起来
    connectPerson(temPerson, headPerson);
   
    return headPerson;
}


int main(int argc, const char * argv[])
{
    printf("请输入玩游戏的人数的个数：\n");
    int count = 0;
    scanf("%d", &count);
    
    printf("请输入喊道几的人出圈：\n"); // 当前不能设置第一个人
    int value = 0;
    scanf("%d", &value);
    
    if (value <= 0) {
        value = 3;
    }
    if (count <= 0) {
        count = 10;
    }
    
    Person * person = initGame(count, value);
    
    Person *temp = person;
    
    while (temp ->next != temp) {
        setPersonSpeack(temp);
        checkPerson(temp, value);
        //开始转圈
        temp = temp->next;
    }
    
    return 0;
}


