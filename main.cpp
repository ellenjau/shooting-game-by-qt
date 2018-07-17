//H34031259 趙雅蘭 project3  作業說明:
//1.) 用鍵盤上下左右移動大白狗（按鍵盤上的上下左右箭頭）
//2.) 按空白鍵大白狗會發射出叉子
//  - 叉子若射到鬼，鬼hp - 1，玩家score +2分
//  - 叉子若射到鬼掉下來的黃球，兩物體會互相抵消，玩家score +1分
//3.) 若大白狗被黃球打到，大白狗hp – 1，玩家score -1分
//4.) 大白狗的分數與hp秀在右手邊
//5.) 鬼的hp秀在上方，還有對應的hp bar
//6.) 大白狗特異功能是poop, 總共有三次poop機會（超過三次使用會跳出qmessagebox），按shift就可以發射，每次分別會發射出3個poops
//  - 當poop撞到黃球時，黃球會消失，poop不會消失，只會繼續向上移動，且玩家score +2分
//  - 當poop撞到鬼時，每一個poop扣鬼5 hp，玩家score +2分
//7.) 大白狗還有另一個特殊功能，總共有三次freeze機會（超過三次使用會跳出qmessagebox），功能是 按s 就可以 暫停畫面3秒鐘，只剩大白狗可以左右移動 擺放叉子或poop（此時的叉子跟poop也不會移動了）
//    大白狗可以趁此時把叉子或poop擺出來 在敵人等一下會走的路徑
//    直到3秒過後 這些叉子 或 poop 會恢復正常移動 以轟炸敵人～
//8.) 大白狗或鬼 任一方hp<=0時，遊戲就結束了，
//    會有qmessagebox 宣布結果，
//    上方或右方的board的qgraphicstextitem也會有所變化
//    and 畫面上死的那一方會消失～
//9.) 按左上角的toolbar 的rule 會顯示出簡單的遊戲介紹
//10.) enemy 跟player class有用polymorphism，此兩個class一起繼承character class
//11.) fork, poop and enemybullet 這三個class也有用polymorphism，一起繼承weapon class

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


