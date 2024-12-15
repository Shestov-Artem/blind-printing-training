//SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//�����������
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // ��� std::rand � std::srand
#include <ctime>   // ��� std::time

//�����
#include <chrono>

#include <iostream>

using namespace std;

SDL_Renderer* renderer = nullptr;

int application_section = 0; //������ ����������
SDL_Point cursor_pos = { 0, 0 }; //���������� �������

SDL_Texture* finger;  //�������� ���� �������� � ������ �������
bool TextIsCorrect;

bool hints = true;  //����������� ���������
string path_one_word = "words.txt";
string path_many_words = "sentences.txt";
string path_one_word_rus = "words_rus.txt";
string path_many_words_rus = "sentences_rus.txt";
bool keyboard_layout_english = true;

//������ � ��������
std::chrono::high_resolution_clock::time_point start;
std::chrono::high_resolution_clock::time_point end_2;
bool GetTime = false;
bool WordWasCorrect = false;
int OneCountWordWasCorrect = 0;

SDL_Texture* LoadImage(std::string file) {
    SDL_Surface* loadedImage = nullptr;
    SDL_Texture* texture = nullptr;
    loadedImage = IMG_Load(file.c_str());
    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return texture;
}

class WorkWithText {
private:
    TTF_Font* font;
    SDL_Color textColor;
    vector<string> lines; // ������ ��� �������� �����
    bool NewWord;

public:
    string text; //�� ��� � �������
    string word;  //�����, ������� �����  ����������
    bool GetNextWord;
    bool WordWasWriteCorrect; //���������� ��� ����� ���� ����������� ���������

    //�����������
    WorkWithText(string file_path) {
        font = TTF_OpenFont("courier-normal.ttf", 20);
        if (!font) std::cout << "���������� ���������� �������� �����";
        textColor = { 255, 255, 255 };

        //��������� ������ �������� 
        ifstream inputFile(file_path); // ������� ���� � ������ �����
        string line;
        while (std::getline(inputFile, line)) {  // ������ ����� �� �����
            lines.push_back(line); // ��������� ������ � ������
        }
        inputFile.close(); // ��������� ����

        NewWord = true;
        GetNextWord = false;
        WordWasWriteCorrect = false; //���������� ��� ����� ���� ����������� ���������
    }

    //���������� ������� ������� (��������)
    string GetKey(SDL_Event event) {
        string key;
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q: key = "q"; break;
        case SDL_SCANCODE_W: key = "w"; break;
        case SDL_SCANCODE_E: key = "e"; break;
        case SDL_SCANCODE_R: key = "r"; break;
        case SDL_SCANCODE_T: key = "t"; break;
        case SDL_SCANCODE_Y: key = "y"; break;
        case SDL_SCANCODE_U: key = "u"; break;
        case SDL_SCANCODE_I: key = "i"; break;
        case SDL_SCANCODE_O: key = "o"; break;
        case SDL_SCANCODE_P: key = "p"; break;
        case SDL_SCANCODE_A: key = "a"; break;
        case SDL_SCANCODE_S: key = "s"; break;
        case SDL_SCANCODE_D: key = "d"; break;
        case SDL_SCANCODE_F: key = "f"; break;
        case SDL_SCANCODE_G: key = "g"; break;
        case SDL_SCANCODE_H: key = "h"; break;
        case SDL_SCANCODE_J: key = "j"; break;
        case SDL_SCANCODE_K: key = "k"; break;
        case SDL_SCANCODE_L: key = "l"; break;
        case SDL_SCANCODE_Z: key = "z"; break;
        case SDL_SCANCODE_X: key = "x"; break;
        case SDL_SCANCODE_C: key = "c"; break;
        case SDL_SCANCODE_V: key = "v"; break;
        case SDL_SCANCODE_B: key = "b"; break;
        case SDL_SCANCODE_N: key = "n"; break;
        case SDL_SCANCODE_M: key = "m"; break;

        case SDL_SCANCODE_SPACE: key = " "; break;
        }
        return key;
    }

    //���������� ������� ������� (��������)
    string GetCirilicKey(SDL_Event event) {
        string key;
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q: key = "�"; break;
        case SDL_SCANCODE_W: key = "�"; break;
        case SDL_SCANCODE_E: key = "�"; break;
        case SDL_SCANCODE_R: key = "�"; break;
        case SDL_SCANCODE_T: key = "�"; break;
        case SDL_SCANCODE_Y: key = "�"; break;
        case SDL_SCANCODE_U: key = "�"; break;
        case SDL_SCANCODE_I: key = "�"; break;
        case SDL_SCANCODE_O: key = "�"; break;
        case SDL_SCANCODE_P: key = "�"; break;
        case SDL_SCANCODE_LEFTBRACKET: key = "�"; break;
        case SDL_SCANCODE_RIGHTBRACKET: key = "�"; break;
        case SDL_SCANCODE_A: key = "�"; break;
        case SDL_SCANCODE_S: key = "�"; break;
        case SDL_SCANCODE_D: key = "�"; break;
        case SDL_SCANCODE_F: key = "�"; break;
        case SDL_SCANCODE_G: key = "�"; break;
        case SDL_SCANCODE_H: key = "�"; break;
        case SDL_SCANCODE_J: key = "�"; break;
        case SDL_SCANCODE_K: key = "�"; break;
        case SDL_SCANCODE_L: key = "�"; break;
        case SDL_SCANCODE_SEMICOLON: key = "�"; break;
        case SDL_SCANCODE_APOSTROPHE: key = "�"; break;
        case SDL_SCANCODE_Z: key = "�"; break;
        case SDL_SCANCODE_X: key = "�"; break;
        case SDL_SCANCODE_C: key = "�"; break;
        case SDL_SCANCODE_V: key = "�"; break;
        case SDL_SCANCODE_B: key = "�"; break;
        case SDL_SCANCODE_N: key = "�"; break;
        case SDL_SCANCODE_M: key = "�"; break;
        case SDL_SCANCODE_COMMA: key = "�"; break;
        case SDL_SCANCODE_PERIOD: key = "�"; break;

        case SDL_SCANCODE_SPACE: key = " "; break;
        }
        return key;
    }

    //������� �������� ����� �� ����� (������� ������)
    void WriteText(string text1, int y) {
        if (text1 != "") {
            SDL_Surface* surface3 = TTF_RenderText_Solid(font, text1.c_str(), textColor);
            SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
            int textWidth = surface3->w;
            int textHeight = surface3->h;
            int x = (724 - textWidth) / 2;  //724 - ������ ����
            SDL_Rect dstRect3 = { x, y, textWidth, textHeight }; //������� � ���� ������ 
            SDL_RenderCopy(renderer, texture3, NULL, &dstRect3);
        }
    }

    //����� ��������� ����� �� �����
    string GetRandomWord() {
        srand(static_cast<unsigned int>(time(0))); // ���� ��������� ��������� �����
        int randomIndex = std::rand() % lines.size(); // ���������� ��������� ������
        return lines[randomIndex];
    }

    //���������� �� ����� ������� ����� ���������� � �������� ���� �����
    bool CorrectText() {

        for (int i = 0; i < text.length(); i++) {
            if (text[i] != word[i]) return false;
        }

        return true;
    }

    //����� ����� ����� �� �����
    void GetNewWord() {
        if (NewWord) {
            word = GetRandomWord();
            NewWord = false;
        }
    }

    //������� ����� ������� ����� ����������
    void PrintWord() {
        textColor = { 255, 255, 255 };
        WriteText(word, 30);
    }

    //������ ���� ������, ���� ���� �������� ������
    void UncorrectText() {
        if (!CorrectText())
            textColor = { 255, 0, 0 };
    }

    //��������� ������������ � ��� ��� ����� ��� ������ ��������� 
    void AllTextCorrect() {
        if (text == word) {
            WriteText("CORRECT!", 90);
            WordWasWriteCorrect = true;
        }
    }

    //��������� �������� � ������ �����
    void NewWordFunc() {
        if (GetNextWord) {
            NewWord = true;
            text = "";
            GetNextWord = false;
            WordWasWriteCorrect = false;
        }
    }

    //��������� ������ ���������� ������
    void MenuDraw(bool Menu, SDL_Texture* key_board) {
        if (Menu) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            textColor = { 255, 255, 255 };
            SDL_RenderCopy(renderer, key_board, NULL, NULL);

            WriteText("����������� ���� ��� �������� �� ��������", 10);
        }
    }

    //����� ���� ���������� ���������, ���� ���� ��� ������� WordWasCorrect=true ����� �������� ������, � ���� ����� �����, ������� ��� �����
    void AllTextCorrect_time_version(string str) {
        if (text == word) {
            if (OneCountWordWasCorrect == 0) WordWasCorrect = true;
            if (OneCountWordWasCorrect < 3) OneCountWordWasCorrect++;
            WriteText(str, 90);
            WordWasWriteCorrect = true;
        }
    }
    //��������� ������
    void TimerStart() {
        start = std::chrono::high_resolution_clock::now();
    }
    //���������� ������
    void TimerStop() {
        end_2 = std::chrono::high_resolution_clock::now();
    }
    //�������� ����� ������ �����������
    string GetTimeFromTimer() {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_2 - start);

        // ��������� ���������� ������ � �����������
        long long totalMicroseconds = duration.count();
        long long seconds = totalMicroseconds / 1000000; // ���������� ������
        long long milliseconds = (totalMicroseconds % 1000000) / 1000; // ���������� �����������

        // ������������ ������ ����������
        string str = "Seconds: " + std::to_string(seconds) + ", Milliseconds: " + std::to_string(milliseconds);

        return str;
    }
};

class WorkWithImage {
private:
    SDL_Texture* finger_1;
    SDL_Texture* finger_2;
    SDL_Texture* finger_3;
    SDL_Texture* finger_4;
    SDL_Texture* finger_5;
    SDL_Texture* finger_6;
    SDL_Texture* finger_7;
    SDL_Texture* finger_8;

    //��������� ������ �������, �� ������� ���� ������
    SDL_Texture* right_key;
    SDL_Rect dest;

public:
    //�����
    SDL_Texture* key_board_rus;
    SDL_Texture* key_board_eng;
    SDL_Texture* key_board_guide_rus;
    SDL_Texture* key_board_guide_eng;

    //������������
    WorkWithImage() {
        key_board_rus = LoadImage("Big_keyboard_rus.png");
        key_board_eng = LoadImage("Big_keyboard_eng.png");
        key_board_guide_rus = LoadImage("Big_keyboard_guide_rus.png");
        key_board_guide_eng = LoadImage("Big_keyboard_guide_rus.png");
        right_key = LoadImage("right_key_2.png");
        SDL_QueryTexture(right_key, NULL, NULL, &dest.w, &dest.h);
        dest.w = 37;
        dest.h = 37;
        dest.x = 100;
        dest.y = 100;

        finger_1 = LoadImage("left_hand_5.png");
        finger_2 = LoadImage("left_hand_4.png");
        finger_3 = LoadImage("left_hand_3.png");
        finger_4 = LoadImage("left_hand_2.png");
        finger_5 = LoadImage("right_hand_2.png");
        finger_6 = LoadImage("right_hand_3.png");
        finger_7 = LoadImage("right_hand_4.png");
        finger_8 = LoadImage("right_hand_5.png");
    }

    //������� ���������� �� ������� ���� ���������� �������� ������ ������� 
    SDL_Point GetXYcoordinates(char ch) { // ��������� ���������� ��� ����������� ������������ ������ �������
        SDL_Point point;
        switch (ch)
        {
        case 'q': point.x = 86; point.y = 190; break;   //Q
        case 'w': point.x = 132; point.y = 190; break;  //W
        case 'e': point.x = 179; point.y = 190; break;  //E
        case 'r': point.x = 225; point.y = 190; break;  //R
        case 't': point.x = 272; point.y = 190; break;  //T
        case 'y': point.x = 318; point.y = 190; break;  //Y
        case 'u': point.x = 364; point.y = 190; break;  //U
        case 'i': point.x = 411; point.y = 190; break;  //I
        case 'o': point.x = 457; point.y = 190; break;  //O
        case 'p': point.x = 504; point.y = 190; break;  //P
        case 'a': point.x = 95; point.y = 234; break;   //A
        case 's': point.x = 142; point.y = 234; break;  //S
        case 'd': point.x = 188; point.y = 234; break;  //D
        case 'f': point.x = 235; point.y = 234; break;  //F
        case 'g': point.x = 282; point.y = 234; break;  //G
        case 'h': point.x = 329; point.y = 234; break;  //H
        case 'j': point.x = 376; point.y = 234; break;  //J
        case 'k': point.x = 422; point.y = 234; break;  //K
        case 'l': point.x = 469; point.y = 234; break;  //L

        case 'z': point.x = 73 + 42; point.y = 281; break;   //Z
        case 'x': point.x = 119 + 42; point.y = 281; break;  //X
        case 'c': point.x = 167 + 42; point.y = 281; break;  //C
        case 'v': point.x = 213 + 42; point.y = 281; break;  //V
        case 'b': point.x = 260 + 42; point.y = 281; break;  //B
        case 'n': point.x = 307 + 42; point.y = 281; break;  //N
        case 'm': point.x = 354 + 42; point.y = 281; break;  //M


        case '�': point.x = 86; point.y = 190; break;   //Q
        case '�': point.x = 132; point.y = 190; break;  //W
        case '�': point.x = 179; point.y = 190; break;  //E
        case '�': point.x = 225; point.y = 190; break;  //R
        case '�': point.x = 272; point.y = 190; break;  //T
        case '�': point.x = 318; point.y = 190; break;  //Y
        case '�': point.x = 364; point.y = 190; break;  //U
        case '�': point.x = 411; point.y = 190; break;  //I
        case '�': point.x = 457; point.y = 190; break;  //O
        case '�': point.x = 504; point.y = 190; break;  //P
        case '�': point.x = 550; point.y = 190; break;  //P
        case '�': point.x = 597; point.y = 190; break;  //P

        case '�': point.x = 95; point.y = 234; break;   //A
        case '�': point.x = 142; point.y = 234; break;  //S
        case '�': point.x = 188; point.y = 234; break;  //D
        case '�': point.x = 235; point.y = 234; break;  //F
        case '�': point.x = 282; point.y = 234; break;  //G
        case '�': point.x = 329; point.y = 234; break;  //H
        case '�': point.x = 376; point.y = 234; break;  //J
        case '�': point.x = 422; point.y = 234; break;  //K
        case '�': point.x = 469; point.y = 234; break;  //L
        case '�': point.x = 515; point.y = 234; break;  //L
        case '�': point.x = 562; point.y = 234; break;  //L

        case '�': point.x = 73 + 42; point.y = 280; break;   //Z
        case '�': point.x = 119 + 42; point.y = 280; break;  //X
        case '�': point.x = 167 + 43; point.y = 280; break;  //C
        case '�': point.x = 213 + 42; point.y = 280; break;  //V
        case '�': point.x = 260 + 42; point.y = 280; break;  //B
        case '�': point.x = 307 + 42; point.y = 280; break;  //N
        case '�': point.x = 354 + 42; point.y = 280; break;  //M
        case '�': point.x = 400 + 42; point.y = 280; break;  //M
        case '�': point.x = 446 + 42; point.y = 280; break;  //M

        case ' ': point.x = 135 + 52; point.y = 330; break;  //SPACE
        default:
            break;
        }
        return point;
    }

    //���������, �������� � ����� ����������� ������� ����� �������
    SDL_Texture* GetRightHand(char ch) {
        if (ch == 'q' or ch == 'a' or ch == 'z' or ch == '�' or ch == '�' or ch == '�')  return  finger_1;     //Q A Z 
        else if (ch == 'w' or ch == 's' or ch == 'x' or ch == '�' or ch == '�' or ch == '�') return  finger_2; //W S X
        else if (ch == 'e' or ch == 'd' or ch == 'c' or ch == '�' or ch == '�' or ch == '�') return  finger_3; //E D C
        else if (ch == 'r' or ch == 'f' or ch == 'v' or ch == 't' or ch == 'g' or ch == 'b' or ch == '�' or ch == '�' or ch == '�' or ch == '�' or ch == '�' or ch == '�') return  finger_4; //R F V T G B
        else if (ch == 'y' or ch == 'h' or ch == 'n' or ch == 'u' or ch == 'j' or ch == 'm' or ch == '�' or ch == '�' or ch == '�' or ch == '�' or ch == '�' or ch == '�') return  finger_5; //Y H N U J M
        else if (ch == 'i' or ch == 'k' or ch == '�' or ch == '�' or ch == '�') return  finger_6; //I K 
        else if (ch == 'o' or ch == 'l' or ch == '�' or ch == '�' or ch == '�') return  finger_7; //O L
        else if (ch == 'p' or ch == '�' or ch == '�' or ch == '�' or ch == '�' or ch == '�') return  finger_8; //P
    }

    //������������ ��������� � �������� �����������
    void DrawRightKey(string word, string text) {

        if (TextIsCorrect && text != word) {

            //������ ������� ������ �������
            char ch = word[text.length()]; //������� ���� �����, �������� ���� ����� ����������
            SDL_Point point = GetXYcoordinates(ch);
            dest.x = point.x;
            dest.y = point.y;
            SDL_RenderCopy(renderer, right_key, NULL, &dest);

            if (ch == ' ') { //����������� ������ ����� ����������� ������������
                for (int i = 0; i < 7; i++) {
                    dest.x += 37;
                    SDL_RenderCopy(renderer, right_key, NULL, &dest);
                }
            }

            //������ ����� ������� ���� ������
            dest.x += 20;
            dest.y += 20;
            finger = GetRightHand(ch);
            if (ch != ' ') SDL_RenderCopy(renderer, finger, NULL, &dest);
        }
    }
};

class Button {
public:

    int x;
    int y;
    int width;
    int height;
    bool is_available = true;  //���� �� ������ � ������
    TTF_Font* font;  //����� ������ �� �������
    SDL_Color textColor;  //���� ������ �� �������
    string button_name = "";

    //�����������
    Button(int x_pos, int y_pos, int w, int h, string name) {
        x = x_pos;
        y = y_pos;
        width = w;
        height = h;
        button_name = name;

        font = TTF_OpenFont("Machine.ttf", 10);
        if (!font) std::cout << "���������� ���������� �������� �����";
        textColor = { 255, 255, 255 };
    }

    //�������� ��� ������ ��������� ��� �������
    bool IfCursorOnButton() {
        if (cursor_pos.x > x && cursor_pos.x < x + width && cursor_pos.y > y && cursor_pos.y < y + height) return true;
        else return false;
    }

    //������� �������� ����� �� ����� (������� ������)
    void WriteButtonName(string text) {
        if (text != "") {
            SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            int textWidth = surface->w;
            int textHeight = surface->h;
            int x_text = x + width - ((x + width - x) / 2) - (textWidth / 2);  //��������� ������
            int y_text = y + height - ((y + height - y) / 2) - (textHeight / 2);
            SDL_Rect dstRect = { x_text, y_text, textWidth, textHeight };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        }
    }

    //��������� ������
    void DrawButton() {

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x, y, x + width, y);
        SDL_RenderDrawLine(renderer, x + width, y, x + width, y + height);
        SDL_RenderDrawLine(renderer, x + width, y + height, x, y + height);
        SDL_RenderDrawLine(renderer, x, y + height, x, y);

        //���� �� ������ ������ ������
        if (IfCursorOnButton()) {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_Rect rect;
            rect.x = x + 1;
            rect.y = y + 1;
            rect.w = width - 1;
            rect.h = height - 1;
            SDL_RenderFillRect(renderer, &rect);
        }

        WriteButtonName(button_name);
    }
};

void WriteStr(string text, int x, int y) {
    TTF_Font* font = TTF_OpenFont("courier-normal.ttf", 20);
    if (!font) std::cout << "���������� ���������� �������� �����";
    SDL_Color textColor = { 255, 255, 255 };
    if (text != "") {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_Rect dstRect = { x, y, textWidth, textHeight }; //������� � ���� ������ 
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("TRAINING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 724, 384, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //������������� ����� ���������� � ��������� ������
    WorkWithText Text = WorkWithText(path_one_word);
    WorkWithText Sentence = WorkWithText(path_many_words);
    WorkWithText Text_rus = WorkWithText(path_one_word_rus);
    WorkWithText Sentence_rus = WorkWithText(path_many_words_rus);

    //������������� ����� ���������� � ���������� �������������
    WorkWithImage Images = WorkWithImage();

    bool Menu = true;  //��������� ���������� ������

    Button menu_button = Button(10, 10, 100, 20, "menu");
    Button setting_button = Button(100, 100, 100, 20, "setting");
    Button training_button = Button(300, 100, 100, 20, "train");
    Button time_training_button = Button(500, 100, 100, 20, "time_train");
    Button enable_hints_button = Button(300, 100, 100, 20, "hints on/off");
    Button change_layout_button = Button(300, 200, 100, 20, "English/Russian");

    string my_speed_time = " "; //����� ��������� �����
    start = std::chrono::high_resolution_clock::now();
    end_2 = std::chrono::high_resolution_clock::now();

    int close = 0;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {// ���������� ���������
            switch (event.type) {
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_KEYDOWN:
                if (keyboard_layout_english) {
                    //���������� ��������
                    if (application_section == 2)
                        if (keyboard_layout_english) Text.text += Text.GetKey(event);
                        else Text.text += Text.GetCirilicKey(event);
                    if (application_section == 3)
                        if (keyboard_layout_english) Sentence.text += Sentence.GetKey(event);
                        else Sentence.text += Sentence.GetCirilicKey(event);

                    //�������� �������� 
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_BACKSPACE:

                        if (application_section == 2)
                            if (Text.text != "") Text.text.pop_back();
                        if (application_section == 3)
                            if (Sentence.text != "") Sentence.text.pop_back();

                        break;
                    case SDL_SCANCODE_DELETE:

                        if (application_section == 2) Text.text = "";
                        if (application_section == 3) Sentence.text = "";

                        break;
                    }

                    //���� ������� ������� ����� ������� � ���� �����
                    if (application_section == 2)
                        if (Text.WordWasWriteCorrect) Text.GetNextWord = true;
                    if (application_section == 3)
                        if (Sentence.WordWasWriteCorrect) Sentence.GetNextWord = true;

                    //���� ������� ������� ����� ��������� ���������
                    if (Menu) {
                        Menu = false;
                        if (application_section == 2) Text.text = "";
                        if (application_section == 3) Sentence.text = "";
                    }
                }
                else {
                    //���������� ��������
                    if (application_section == 2)
                        if (keyboard_layout_english) Text_rus.text += Text_rus.GetKey(event);
                        else Text_rus.text += Text_rus.GetCirilicKey(event);
                    if (application_section == 3)
                        if (keyboard_layout_english) Sentence_rus.text += Sentence_rus.GetKey(event);
                        else Sentence_rus.text += Sentence_rus.GetCirilicKey(event);

                    //�������� �������� 
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_BACKSPACE:

                        if (application_section == 2)
                            if (Text_rus.text != "") Text_rus.text.pop_back();
                        if (application_section == 3)
                            if (Sentence_rus.text != "") Sentence_rus.text.pop_back();

                        break;
                    case SDL_SCANCODE_DELETE:

                        if (application_section == 2) Text_rus.text = "";
                        if (application_section == 3) Sentence_rus.text = "";

                        break;
                    }

                    //���� ������� ������� ����� ������� � ���� �����
                    if (application_section == 2)
                        if (Text_rus.WordWasWriteCorrect) Text_rus.GetNextWord = true;
                    if (application_section == 3)
                        if (Sentence_rus.WordWasWriteCorrect) Sentence_rus.GetNextWord = true;

                    //���� ������� ������� ����� ��������� ���������
                    if (Menu) {
                        Menu = false;
                        if (application_section == 2) Text_rus.text = "";
                        if (application_section == 3) Sentence_rus.text = "";
                    }
                }
            case SDL_MOUSEBUTTONDOWN:
                // API ���������� ��� ����������� ������� ������ ����
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (menu_button.IfCursorOnButton() && menu_button.is_available) {
                        application_section = 0;
                    }
                    if (setting_button.IfCursorOnButton() && setting_button.is_available) {
                        application_section = 1;
                    }
                    if (training_button.IfCursorOnButton() && training_button.is_available) {
                        application_section = 2;
                    }
                    if (time_training_button.IfCursorOnButton() && time_training_button.is_available) {
                        application_section = 3;
                    }
                    if (enable_hints_button.IfCursorOnButton() && enable_hints_button.is_available) {
                        hints = !hints;
                    }
                    if (change_layout_button.IfCursorOnButton() && change_layout_button.is_available) {
                        keyboard_layout_english = !keyboard_layout_english;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        //�������� ���������� ����
        SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);

        switch (application_section)
        {
        case 0: //����
            menu_button.is_available = false;
            setting_button.is_available = true;
            training_button.is_available = true;
            time_training_button.is_available = true;
            enable_hints_button.is_available = false;
            change_layout_button.is_available = false;

            Menu = true;  //��������� ���������� ������

            setting_button.DrawButton();
            training_button.DrawButton();
            time_training_button.DrawButton();
            break;

        case 1: //���������
            if (hints) enable_hints_button.button_name = "hints on";
            else enable_hints_button.button_name = "hints off";

            if (keyboard_layout_english) change_layout_button.button_name = "English";
            else change_layout_button.button_name = "Russian";

            menu_button.is_available = true;
            setting_button.is_available = false;
            training_button.is_available = false;
            time_training_button.is_available = false;
            enable_hints_button.is_available = true;
            change_layout_button.is_available = true;

            //������ ��������
            WriteStr("����������� ���������:", 10, 100);  //����������� ���������
            WriteStr("����� ���������:", 10, 200);  //����� ���������

            menu_button.DrawButton();
            enable_hints_button.DrawButton();
            change_layout_button.DrawButton();

            break;

        case 2: //���������� � ����� ������

            menu_button.is_available = true;
            setting_button.is_available = false;
            training_button.is_available = false;
            time_training_button.is_available = false;
            enable_hints_button.is_available = false;
            change_layout_button.is_available = false;

            if (keyboard_layout_english) {
                SDL_RenderCopy(renderer, Images.key_board_eng, NULL, NULL);
                Text.GetNewWord(); //����� ����� �� �����
                Text.PrintWord(); //�������� ����� �� �����
                TextIsCorrect = Text.CorrectText();  //�������, ��������� �� �������� �����
                if (hints) Images.DrawRightKey(Text.word, Text.text); //������ ����� ������� ����� ������
                Text.UncorrectText(); //������ ����� �������, ���� � ����� ���� �������� ������
                Text.WriteText(Text.text, 60); //���������� ���������� �����
                Text.AllTextCorrect(); //��������� ��� ����� ���� ����������� ���������
                Text.NewWordFunc(); //����� ����� �����
                Text.MenuDraw(Menu, Images.key_board_guide_eng); //��������� ���������� ������
            }
            else {
                SDL_RenderCopy(renderer, Images.key_board_rus, NULL, NULL);
                Text_rus.GetNewWord(); //����� ����� �� �����
                Text_rus.PrintWord(); //�������� ����� �� �����
                TextIsCorrect = Text_rus.CorrectText();  //�������, ��������� �� �������� �����
                if (hints) Images.DrawRightKey(Text_rus.word, Text_rus.text); //������ ����� ������� ����� ������
                Text_rus.UncorrectText(); //������ ����� �������, ���� � ����� ���� �������� ������
                Text_rus.WriteText(Text_rus.text, 60); //���������� ���������� �����
                Text_rus.AllTextCorrect(); //��������� ��� ����� ���� ����������� ���������
                Text_rus.NewWordFunc(); //����� ����� �����
                Text_rus.MenuDraw(Menu, Images.key_board_guide_rus); //��������� ���������� ������
            }

            menu_button.DrawButton();

            break;

        case 3: //���������� �� �����

            menu_button.is_available = true;
            setting_button.is_available = false;
            training_button.is_available = false;
            time_training_button.is_available = false;
            enable_hints_button.is_available = false;
            change_layout_button.is_available = false;

            if (keyboard_layout_english) {
                SDL_RenderCopy(renderer, Images.key_board_eng, NULL, NULL);   //������ ����������
                Sentence.GetNewWord();                                        //����� ����� �� �����
                Sentence.PrintWord();                                         //�������� ����� �� �����
                TextIsCorrect = Sentence.CorrectText();                       //�������, ��������� �� �������� �����
                if (hints) Images.DrawRightKey(Sentence.word, Sentence.text); //������ ����� ������� ����� ������
                Sentence.UncorrectText();                                     //������ ����� �������, ���� � ����� ���� �������� ������
                Sentence.WriteText(Sentence.text, 60);                        //���������� ���������� �����

                //������ � ��������
                if (WordWasCorrect) GetTime = true;
                WordWasCorrect = false;
                if (Sentence.GetNextWord) OneCountWordWasCorrect = 0;
                if (GetTime) {
                    Sentence.TimerStop();
                    my_speed_time = Sentence.GetTimeFromTimer();
                    Sentence.TimerStart();
                }
                Sentence.AllTextCorrect_time_version(my_speed_time);
                GetTime = false;
                //������ � ��������

                Sentence.NewWordFunc();                                       //����� ����� �����
                Sentence.MenuDraw(Menu, Images.key_board_guide_eng);          //��������� ���������� ������
            }
            else {
                SDL_RenderCopy(renderer, Images.key_board_rus, NULL, NULL);           //������ ����������
                Sentence_rus.GetNewWord();                                            //����� ����� �� �����
                Sentence_rus.PrintWord();                                             //�������� ����� �� �����
                TextIsCorrect = Sentence_rus.CorrectText();                           //�������, ��������� �� �������� �����
                if (hints) Images.DrawRightKey(Sentence_rus.word, Sentence_rus.text); //������ ����� ������� ����� ������
                Sentence_rus.UncorrectText();                                         //������ ����� �������, ���� � ����� ���� �������� ������
                Sentence_rus.WriteText(Sentence_rus.text, 60);                        //���������� ���������� �����
                 
                //������ � ��������
                if (WordWasCorrect) GetTime = true;
                WordWasCorrect = false;
                if (Sentence_rus.GetNextWord) OneCountWordWasCorrect = 0;
                if (GetTime) {
                    Sentence_rus.TimerStop();
                    my_speed_time = Sentence_rus.GetTimeFromTimer();
                    Sentence_rus.TimerStart();
                }
                Sentence_rus.AllTextCorrect_time_version(my_speed_time);
                GetTime = false;
                //������ � ��������

                Sentence_rus.NewWordFunc();                                            //����� ����� �����
                Sentence_rus.MenuDraw(Menu, Images.key_board_guide_rus);               //��������� ���������� ������
            }

            menu_button.DrawButton();

            break;
        default:
            break;
        }
        SDL_RenderPresent(renderer);
    }

    // �������� ���� � ���������� ������ SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}