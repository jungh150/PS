#include <iostream>
using namespace std;

int n;

void f(int x) {
    if (x > n) {
        return;
    } else if (x == n) {
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "\"����Լ��� ������?\"\n";
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n";
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "��� �亯�Ͽ���.\n";
    } else {
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "\"����Լ��� ������?\"\n";
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n";
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n";
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n";
        f(x + 1);
        for (int i = 0; i < 4 * x; i++) cout << '_';
        cout << "��� �亯�Ͽ���.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n";

    f(0);
}
