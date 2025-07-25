#include <bits/stdc++.h>

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<> dist(0, 24);

enum Stat {
    Atk = 0,
    Def,
    SpA,
    SpD,
    Spe,
    StatCount
};

const std::string StatNames[StatCount] = {
    "物攻", "物抗", "魔攻", "魔抗", "速度"
};

struct Nature {
    int increase;
    int decrease;
    std::string name;
};

const std::vector<Nature> Natures = {
    {Atk, Def, "孤僻"}, {Atk, SpA, "固执"}, {Atk, SpD, "调皮"}, {Atk, Spe, "勇敢"}, {Atk, Atk, "坦率"},
    {Def, Atk, "大胆"}, {Def, SpA, "淘气"}, {Def, SpD, "无虑"}, {Def, Spe, "悠闲"}, {Def, Def, "害羞"},
    {SpA, Atk, "保守"}, {SpA, Def, "稳重"}, {SpA, SpD, "马虎"}, {SpA, Spe, "冷静"}, {SpA, SpA, "认真"},
    {SpD, Atk, "沉着"}, {SpD, Def, "温顺"}, {SpD, SpA, "慎重"}, {SpD, Spe, "狂妄"}, {SpD, SpD, "实干"},
    {Spe, Atk, "胆小"}, {Spe, Def, "急躁"}, {Spe, SpA, "开朗"}, {Spe, SpD, "天真"}, {Spe, Spe, "浮躁"}
};

int randCount = 1;
std::vector<std::tuple<int, std::string, std::string, std::string>> logRecords;

void logNature() {
    int natureIndex = dist(rng);
    Nature selectedNature = Natures[natureIndex];

    std::string increase = StatNames[selectedNature.increase];
    std::string decrease = StatNames[selectedNature.decrease];
    std::string name = selectedNature.name;

    std::cout << std::setw(4) << randCount << " | "
              << std::left << std::setw(6) << name << " | "
              << std::setw(6) << increase << "↑ | "
              << std::setw(6) << decrease << "↓ |" << "\n";

    logRecords.emplace_back(randCount, name, increase, decrease);
    randCount++;
}

void saveCSV(const std::string& filename = "natures.csv") {
    std::ofstream out(filename);
    out << "编号,性格,提升属性,降低属性\n";
    for (auto [id, name, inc, dec] : logRecords) {
        out << id << "," << name << "," << inc << "," << dec << "\n";
    }
    out.close();
    std::cout << "\n日志已保存至: " << filename << "\n";
}

void fixedMode() {
    int count;
    std::cout << "请输入生成的性格数量：";
    std::cin >> count;
    std::cin.ignore();

    std::cout << "\n生成结果：\n";
    for (int i = 0; i < count; ++i) {
        logNature();
    }
    saveCSV();
}

void manualMode() {
    std::string input;
    std::cout << "按 Enter 生成随机性格，输入 q 回车退出并保存。\n";
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") break;
        logNature();
    }
    saveCSV();
}

int main() {
    std::cout << "===== 性格生成器 =====\n";
    std::cout << "请选择模式：\n";
    std::cout << "1. 固定次数模式\n";
    std::cout << "2. 手动随机模式\n";
    std::cout << "=======================\n";
    std::cout << "输入模式编号：";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        fixedMode();
    } else if (choice == 2) {
        manualMode();
    } else {
        std::cout << "无效选择，程序结束。\n";
    }

    return 0;
}
