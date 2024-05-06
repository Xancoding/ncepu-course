#include <iostream>
#include <string>
#include <vector>
#include <memory>  // For smart pointers (optional)
#include <utility>

using namespace std;

class Player {
public:
    // 构造函数，初始化球员姓名、年龄、位置和号码
    Player(const string& name, int age, const string& position, int number)
            : name(name), age(age), position(position), number(number) {}

    // 析构函数，用于释放资源
    virtual ~Player() = default;  // Virtual destructor for proper cleanup with subclasses

    // 获取球员姓名
    string getName() const { return name; }

    // 获取球员年龄
    int getAge() const { return age; }

    // 获取球员位置
    string getPosition() const { return position; }

    // 获取球员号码
    int getNumber() const { return number; }

    // 虚拟函数，用于显示球员信息
    virtual void displayInfo() const {
        cout << "Player Information:" << endl;
        cout << "  Name: " << name << endl;
        cout << "  Age: " << age << endl;
        cout << "  Position: " << position << endl;
        cout << "  Number: " << number << endl;
    }

private:
    // 球员姓名
    string name;

    // 球员年龄
    int age;

    // 球员位置
    string position;

    // 球员号码
    int number;
};

class Coach {
public:
    // 构造函数，初始化教练姓名、年龄和执教经验
    Coach(const string& name, int age, int experience)
            : name(name), age(age), experience(experience) {}

    // 获取教练姓名
    string getName() const { return name; }

    // 获取教练年龄
    int getAge() const { return age; }

    // 获取教练执教经验
    int getExperience() const { return experience; }

    // 显示教练信息
    void displayInfo() const {
        cout << "Coach Information:" << endl;
        cout << "  Name: " << name << endl;
        cout << "  Age: " << age << endl;
        cout << "  Experience: " << experience << " years" << endl;
    }

private:
    // 教练姓名
    string name;

    // 教练年龄
    int age;

    // 教练执教经验
    int experience;
};

class FootballTeam {
public:
    // 构造函数，初始化球队名称、教练和球员
    FootballTeam(const string& name, const shared_ptr<Coach>& coach, const vector<Player>& players)
            : name(name), coach(coach), players(players) {}

    // 获取球队名称
    string getName() const { return name; }

    // 获取球队教练
    const shared_ptr<Coach>& getCoach() const { return coach; }

    // 获取球队所有球员
    const vector<Player>& getPlayers() const { return players; }

    // 显示球队信息
    void displayInfo() const {
        cout << "Team Information:" << endl;
        cout << "  Name: " << name << endl;
        cout << "  Coach: ";
        coach->displayInfo();  // 使用 `Coach` 类对象的 `displayInfo` 函数
        cout << "  Players:" << endl;
        for (const Player& player : players) {
            player.displayInfo();
        }
    }

    // 添加成员函数 `replacePlayer`，用于替换队员
    void replacePlayer(const string& oldPlayerName, const shared_ptr<Player>& newPlayer) {
        // 遍历球队所有球员，找到要替换的球员
        for (auto it = players.begin(); it != players.end(); ++it) {
            if (it->getName() == oldPlayerName) {
                // 将要替换的球员从球队中移除
                players.erase(it);
                break;
            }
        }

        // 将新球员添加到球队中
        players.push_back(*newPlayer);
    }

    // 添加成员函数 `promotePlayerToCoach`，用于提升球员为主教练
    void promotePlayerToCoach(const string& playerName) {
        // 找到要提升的球员
        for (auto it = players.begin(); it != players.end(); ++it) {
            if (it->getName() == playerName) {
                // 将该球员提升为主教练
                coach = make_shared<Coach>(it->getName(), it->getAge(), 0);  // 使用球员信息创建新的 Coach 对象
                players.erase(it);  // 从球员列表中移除该球员
                break;
            }
        }
    }


private:
    // 球队名称
    string name;

    // 球队教练
    shared_ptr<Coach> coach;  // 改为 `Coach` 类对象

    // 球队所有球员
    vector<Player> players;
};
;
class Match {
public:
    // 构造函数，初始化比赛主队、客队、日期、地点和比分
    Match(const shared_ptr<FootballTeam>& homeTeam, const shared_ptr<FootballTeam>& awayTeam,
          const string& date, const string& location, const string& score)
            : homeTeam(homeTeam), awayTeam(awayTeam), date(date), location(location), score(score) {}

    // 获取比赛主队
    const shared_ptr<FootballTeam>& getHomeTeam() const { return homeTeam; }

    // 获取比赛客队
    const shared_ptr<FootballTeam>& getAwayTeam() const { return awayTeam; }

    // 显示比赛信息
    void displayInfo() const {
        cout << "Match Information:" << endl;
        cout << "  Home Team: " << homeTeam->getName() << endl;  // 使用 `FootballTeam` 类对象的 `getName` 函数
        cout << "  Away Team: " << awayTeam->getName() << endl;  // 使用 `FootballTeam` 类对象的 `getName` 函数
        cout << "  Date: " << date << endl;
        cout << "  Location: " << location << endl;
        cout << "  Score: " << score << endl;
    }

private:
    // 比赛主队
    shared_ptr<FootballTeam> homeTeam;

    // 比赛客队
    shared_ptr<FootballTeam> awayTeam;

    // 比赛日期
    string date;

    // 比赛地点
    string location;

    // 比赛比分
    string score;
};;

int main() {
    // 创建2个教练对象
    shared_ptr<Coach> coach1(new Coach("John Smith", 50, 20));
    shared_ptr<Coach> coach2(new Coach("Jurgen Klopp", 54, 25));

    // 创建多个球员对象
    shared_ptr<Player> player1(new Player("Cristiano Ronaldo", 37, "Forward", 7));
    shared_ptr<Player> player2(new Player("Bruno Fernandes", 27, "Midfielder", 18));
    shared_ptr<Player> player3(new Player("Mohamed Salah", 30, "Forward", 11));
    shared_ptr<Player> player4(new Player("Virgil van Dijk", 31, "Defender", 4));
    shared_ptr<Player> player5(new Player("Harry Maguire", 29, "Defender", 5));
    shared_ptr<Player> player6(new Player("David de Gea", 31, "Goalkeeper", 1));
    shared_ptr<Player> player7(new Player("Alisson Becker", 29, "Goalkeeper", 1));
    shared_ptr<Player> player8(new Player("Roberto Firmino", 30, "Forward", 9));

    vector<Player> players1;
    players1.push_back(*player1);
    players1.push_back(*player2);
    players1.push_back(*player5);
    players1.push_back(*player6);

    vector<Player> players2;
    players2.push_back(*player3);
    players2.push_back(*player4);
    players2.push_back(*player7);
    players2.push_back(*player8);


    shared_ptr<FootballTeam> team1(new FootballTeam("Manchester United", coach1, players1));
    shared_ptr<FootballTeam> team2(new FootballTeam("Liverpool", coach2, players2));


    // 创建3个比赛对象
    Match match1(team1, team2, "2023-11-16", "Old Trafford", "2-1");
    Match match2(team2, team1, "2023-12-03", "Anfield", "1-1");
    Match match3(team1, team2, "2024-01-01", "Wembley Stadium", "0-0");

    // 显示所有比赛信息
    match1.displayInfo();
    cout << endl;
    match2.displayInfo();
    cout << endl;
    match3.displayInfo();

    // 替换球员
    shared_ptr<Player> player9(new Player("Lionel Messi", 34, "Forward", 30));
    team1->replacePlayer("Cristiano Ronaldo", player9);
    team1->displayInfo();

    // 提升球员为主教练
    team1->promotePlayerToCoach("Bruno Fernandes");
    team1->displayInfo();


    return 0;
}
