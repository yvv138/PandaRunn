#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

void copyArrayToQueue(const int* array, int size, std::queue<int>& queue) {
    for (int i = 0; i < size; ++i) {
        queue.push(array[i]);
        if (queue.size() > 10) {
            queue.pop();  
        }
    }
}

void copyQueueToArray(std::queue<int>& kolejka, int* tablica, int rozmiar) {
    int index = 0;
    while (!kolejka.empty() && index < rozmiar) {
        tablica[index] = kolejka.front();
        kolejka.pop();
        index++;
    }
}

void ReadFileToFifoQueue(const std::string& filename, std::queue<int>& fifoQueue)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        int number;
        while (file >> number)
        {
            fifoQueue.push(number);
        }
        file.close();
    }  
    else
    {
        std::cout << "Błąd wczytywania pliku." << std::endl;
    }
}

void saveQueueToFile(const std::queue<int>& queue, const std::string& filename) {
    std::ofstream file(filename);
    std::queue<int> tempQueue = queue;
    while (!tempQueue.empty()) {
        file << tempQueue.front() << std::endl;
        tempQueue.pop();
    }
    file.close();
}

class Obstacle {
public:
    sf::Sprite sprite;
    float speed;
    int textureIndex; 
    Obstacle(sf::Texture& texture, sf::Texture& texture2, float obstacleSpeed)
        : speed(obstacleSpeed) {
        sprite.setTexture(texture); 
        textureIndex = 0; 
    }
    void update() {
        sprite.move(-speed, 0);
    }
};

struct fall
{
    bool tablica;
    bool gra;
    bool menu;
};

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    int pkt = 0;
    const int windowWidth = 800;
    const int windowHeight = 400;
    bool collision = false; 
    int maxSize = 10;
    sf::Clock scoreClock;
    std::queue<int> fifoQueue;
    ReadFileToFifoQueue("score.txt", fifoQueue);
    int arr[10];
    copyQueueToArray(fifoQueue, arr, 10);
    copyArrayToQueue(arr, 10, fifoQueue);
    fall prze;
    prze.gra = false;
    prze.tablica = false;
    prze.menu = true;

    sf::RenderWindow window(sf::VideoMode(800, 400), "PANDA RUN", sf::Style::Titlebar | sf::Style::Close);
    
    std::vector<Obstacle> obstacles;
    int spawnInterval = 1500; 
    int maxObstacleCount = 3; 
    sf::Clock clock;
    sf::Time lastSpawnTime = clock.getElapsedTime();

    sf::Font font;
    if (!font.loadFromFile("Play-Regular.ttf")) {
        std::cout << "Błąd wczytywania czcionki." << std::endl;
        return 1;
    }
 
    sf::Texture textlogo;
    if (!textlogo.loadFromFile("logo.png")) 
    {
       std::cout << "Błąd wczytania obrazu." << std::endl;
        return 1;
    }

    sf::Sprite logo(textlogo);
    logo.setPosition(90, 100);
    logo.setScale(0.3f, 0.3f);

    sf::Text tekstPunktow;
    tekstPunktow.setFont(font);
    tekstPunktow.setCharacterSize(30);
    tekstPunktow.setFillColor(sf::Color::Black);
    tekstPunktow.setPosition(550, 10);

    sf::Text options("       Play \n Scoreboard", font, 24);
    options.setFillColor(sf::Color::Black);
    options.setPosition(320, 200);

    sf::Text tut("S to play    T for scoreboard    M for menu", font ,15);
    tut.setFillColor(sf::Color::Black);
    tut.setPosition(260, 380);

    sf::Text wyniki("Last 10 results ", font, 24);
    wyniki.setFillColor(sf::Color::Black);
    wyniki.setPosition(320, 30);

    sf::Text wynikijeden;
    wynikijeden.setFont(font);
    wynikijeden.setFillColor(sf::Color::Black);
    wynikijeden.setPosition(320, 70);

    sf::Text wynikidwa;
    wynikidwa.setFont(font);
    wynikidwa.setFillColor(sf::Color::Black);
    wynikidwa.setPosition(320, 100);

    sf::Text wynikitrzy;
    wynikitrzy.setFont(font);
    wynikitrzy.setFillColor(sf::Color::Black);
    wynikitrzy.setPosition(320, 130);

    sf::Text wynikicztery;
    wynikicztery.setFont(font);
    wynikicztery.setFillColor(sf::Color::Black);
    wynikicztery.setPosition(320, 160);

    sf::Text wynikipienc;
    wynikipienc.setFont(font);
    wynikipienc.setFillColor(sf::Color::Black);
    wynikipienc.setPosition(320, 190);

    sf::Text wynikiszesc;
    wynikiszesc.setFont(font);
    wynikiszesc.setFillColor(sf::Color::Black);
    wynikiszesc.setPosition(320, 220);

    sf::Text wynikisiedem;
    wynikisiedem.setFont(font);
    wynikisiedem.setFillColor(sf::Color::Black);
    wynikisiedem.setPosition(320, 250);

    sf::Text wynikiosiem;
    wynikiosiem.setFont(font);
    wynikiosiem.setFillColor(sf::Color::Black);
    wynikiosiem.setPosition(320, 280);

    sf::Text wynikidziew;
    wynikidziew.setFont(font);
    wynikidziew.setFillColor(sf::Color::Black);
    wynikidziew.setPosition(320, 310);

    sf::Text wynikidziesienc;
    wynikidziesienc.setFont(font);
    wynikidziesienc.setFillColor(sf::Color::Black);
    wynikidziesienc.setPosition(320, 340);

    sf::Text text("Press R to restart", font, 24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(300, 200);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture1;
    if (!backgroundTexture.loadFromFile("background1.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("background2.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture3;
    if (!backgroundTexture3.loadFromFile("background3.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture4;
    if (!backgroundTexture4.loadFromFile("background4.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture5;
    if (!backgroundTexture5.loadFromFile("background5.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    sf::Texture krzaki;
    if (!krzaki.loadFromFile("krzaki.png")) {
        std::cout << "Błąd wczytywania tekstury tła." << std::endl;
        return 1;
    }

    backgroundTexture.loadFromFile("background.png");
    backgroundTexture1.loadFromFile("background1.png");
    backgroundTexture2.loadFromFile("background2.png");
    backgroundTexture3.loadFromFile("background3.png");
    backgroundTexture4.loadFromFile("background4.png");
    backgroundTexture5.loadFromFile("background5.png");
    krzaki.loadFromFile("krzaki.png");

    sf::Sprite backgroundSprite1(backgroundTexture);
    sf::Sprite backgroundSprite2(backgroundTexture);
    sf::Sprite backgroundSprite3(backgroundTexture1);
    sf::Sprite backgroundSprite4(backgroundTexture1);
    sf::Sprite backgroundSprite5(backgroundTexture2);
    sf::Sprite backgroundSprite6(backgroundTexture2);
    sf::Sprite backgroundSprite7(backgroundTexture3);
    sf::Sprite backgroundSprite8(backgroundTexture3);
    sf::Sprite backgroundSprite9(backgroundTexture4);
    sf::Sprite backgroundSprite10(backgroundTexture4);
    sf::Sprite backgroundSprite11(backgroundTexture5);
    sf::Sprite backgroundSprite12(backgroundTexture5);
    sf::Sprite duchkrz(krzaki);
    sf::Sprite duchkrza(krzaki);

    float scaleRatio = 800.0f / 4096.0f;
    float scaleratioy = 400.0f / 1365.0f;
    duchkrz.setScale(scaleRatio, scaleratioy);
    duchkrza.setScale(scaleRatio, scaleratioy);
    backgroundSprite1.setScale(scaleRatio, scaleratioy);
    backgroundSprite2.setScale(scaleRatio, scaleratioy);
    backgroundSprite3.setScale(scaleRatio, scaleratioy);
    backgroundSprite4.setScale(scaleRatio, scaleratioy);
    backgroundSprite5.setScale(scaleRatio, scaleratioy);
    backgroundSprite6.setScale(scaleRatio, scaleratioy);
    backgroundSprite7.setTexture(backgroundTexture3);
    backgroundSprite8.setTexture(backgroundTexture3);
    backgroundSprite9.setScale(scaleRatio, scaleratioy);
    backgroundSprite10.setScale(scaleRatio, scaleratioy);
    backgroundSprite11.setScale(scaleRatio, scaleratioy);
    backgroundSprite12.setScale(scaleRatio, scaleratioy);
   
    float yOffset = 0.0f;
    duchkrz.setPosition(0.0f, yOffset);
    duchkrza.setPosition(800.0f, yOffset);
    backgroundSprite1.setPosition(0.0f, yOffset);
    backgroundSprite2.setPosition(800.0f, yOffset);
    backgroundSprite3.setPosition(0.0f, yOffset);
    backgroundSprite4.setPosition(800.0f, yOffset);
    backgroundSprite5.setPosition(0.0f, yOffset);
    backgroundSprite6.setPosition(800.0f, yOffset);
    backgroundSprite7.setPosition(0.0f, yOffset);
    backgroundSprite8.setPosition(800.0f, yOffset);
    backgroundSprite9.setPosition(0.0f, yOffset);
    backgroundSprite10.setPosition(800.0f, yOffset);
    backgroundSprite11.setPosition(0.0f, yOffset);
    backgroundSprite12.setPosition(800.0f, yOffset);

    float w = 0.75f;
    float backgroundSpeed = w*2.0f;
    float backgroundSpeeda = w * 4.0f;
    float backgroundSpeedb = w * 2.0f;
    float backgroundSpeedc = w * 3.0f;
    float backgroundSpeedd = w * 1.0f;
    float backgroundSpeede = w * 0.5f;

    sf::Texture obstacleTexture;
    if (!obstacleTexture.loadFromFile("obstacle.png")) {
        std::cout << "Błąd wczytywania tekstury." << std::endl;
        return 1;
    }

    sf::Texture obstacleTexture2;
    if (!obstacleTexture2.loadFromFile("obstacle2.png")) {
        std::cout << "Błąd wczytywania tekstury." << std::endl;
        return 1;
    }
    
    float obstacleYPosition = windowHeight - 100;

    sf::Texture texture;
    if (!texture.loadFromFile("dinozaur.png"))
    {
        std::cout << "Błąd wczytywania tekstury." << std::endl;
    }

    sf::Sprite dinosaur(texture);
    int numFrames = 4;
    int currentFrame = 0;
    dinosaur.setScale(0.1f, 0.1f);
    int frameWidth = texture.getSize().x / numFrames;
    int frameHeight = texture.getSize().y;
    dinosaur.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    dinosaur.setPosition(100, 298);
    int x = window.getSize().y - frameHeight - 50;
    float animationSpeed = 0.02f;
    float totalAnimationTime = animationSpeed * numFrames;
    float elapsedTime = 0.0f;
    sf::Clock zegar;
    bool czywgrze = false;
    bool flag = true;
    bool jump = false;
    float gravity = 10.0f;

    while (window.isOpen())
    {
        if (scoreClock.getElapsedTime().asMilliseconds() >= 100 && !collision && prze.gra) {
            pkt++;
            scoreClock.restart();
        }
        float deltaTime = zegar.restart().asSeconds();
        elapsedTime += deltaTime;
        if (elapsedTime >= totalAnimationTime)
        {
            elapsedTime -= totalAnimationTime;
            currentFrame = (currentFrame + 1) % numFrames;
            if (!collision)
            {
                if (currentFrame < 3)
                {
                    dinosaur.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                }
                else
                {
                    dinosaur.setTextureRect(sf::IntRect(3 * frameWidth, 0, frameWidth, frameHeight));
                }
            }
            else
            {
                dinosaur.setTextureRect(sf::IntRect(3 * frameWidth, 0, frameWidth, frameHeight));
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::S && !czywgrze)
            {
                prze.gra = true;
                prze.menu = false;
                prze.tablica = false;
                czywgrze = true;
                collision = false;
                jump = false;
                gravity = 10.0f;
                pkt = 0;
                flag = true;
                dinosaur.setPosition(100, 298);
                obstacles.clear();
            }
            if (event.key.code == sf::Keyboard::T)
            {
                prze.gra = false;
                prze.menu = false;
                prze.tablica = true;
                czywgrze = false;
                copyQueueToArray(fifoQueue, arr, 10);
                copyArrayToQueue(arr, 10, fifoQueue);
            }
            if (event.key.code == sf::Keyboard::M)
            {
                prze.gra = false;
                prze.menu = true;
                prze.tablica = false;
                czywgrze = false;
            }
            if (event.key.code == sf::Keyboard::Space && !jump && !collision)
            {
                jump = true;
            }
            if (event.key.code == sf::Keyboard::R && collision)
            {
                collision = false;
                jump = false;
                gravity = 10.0f;
                pkt = 0;
                flag = true;
                dinosaur.setPosition(100, 298);
                obstacles.clear();
            }
        }
        if (!collision)
        {
            backgroundSprite3.move(-backgroundSpeeda, 0.0f);
            backgroundSprite4.move(-backgroundSpeeda, 0.0f);
            backgroundSprite5.move(-backgroundSpeedc, 0.0f);
            backgroundSprite6.move(-backgroundSpeedc, 0.0f);
            backgroundSprite7.move(-backgroundSpeedb, 0.0f);
            backgroundSprite8.move(-backgroundSpeedb, 0.0f);
            backgroundSprite9.move(-backgroundSpeedd, 0.0f);
            backgroundSprite10.move(-backgroundSpeedd, 0.0f);
            backgroundSprite11.move(-backgroundSpeede, 0.0f);
            backgroundSprite12.move(-backgroundSpeede, 0.0f);
            duchkrz.move(-backgroundSpeedb, 0.0f);
            duchkrza.move(-backgroundSpeedb, 0.0f);
            if (backgroundSprite3.getPosition().x < -800.0f)
                backgroundSprite3.setPosition(800.0f, yOffset);
            if (backgroundSprite4.getPosition().x < -800.0f)
                backgroundSprite4.setPosition(800.0f, yOffset);
            if (backgroundSprite5.getPosition().x < -800.0f)
                backgroundSprite5.setPosition(800.0f, yOffset);
            if (backgroundSprite6.getPosition().x < -800.0f)
                backgroundSprite6.setPosition(800.0f, yOffset);
            if (backgroundSprite7.getPosition().x < -800.0f)
                backgroundSprite7.setPosition(800.0f, yOffset);
            if (backgroundSprite8.getPosition().x < -800.0f)
                backgroundSprite8.setPosition(800.0f, yOffset);
            if (backgroundSprite9.getPosition().x < -800.0f)
                backgroundSprite9.setPosition(800.0f, yOffset);
            if (backgroundSprite10.getPosition().x < -800.0f)
                backgroundSprite10.setPosition(800.0f, yOffset);
            if (backgroundSprite11.getPosition().x < -800.0f)
                backgroundSprite11.setPosition(800.0f, yOffset);
            if (backgroundSprite12.getPosition().x < -800.0f)
                backgroundSprite12.setPosition(800.0f, yOffset);
            if (duchkrz.getPosition().x < -800.0f)
               duchkrz.setPosition(800.0f, yOffset);
            if (duchkrza.getPosition().x < -800.0f)
                duchkrza.setPosition(800.0f, yOffset);
        }
        sf::Time currentTime = clock.getElapsedTime();
        if (!collision && prze.gra) {
            if (currentTime.asMilliseconds() - lastSpawnTime.asMilliseconds() > spawnInterval &&
                obstacles.size() < maxObstacleCount) {
                float obstacleSpeed = static_cast<float>(rand() % 3 + 2); 
                Obstacle obstacle(obstacleTexture,obstacleTexture2, obstacleSpeed);
                obstacle.sprite.setScale(0.1f, 0.1f);
                obstacle.sprite.setPosition(static_cast<float>(windowWidth), obstacleYPosition);
                obstacle.textureIndex = rand() % 2;
                obstacles.push_back(obstacle);
                lastSpawnTime = currentTime;
            }
        }
        if (!collision && prze.gra) {
            for (auto it = obstacles.begin(); it != obstacles.end();) {
                it->update();
                if (it->sprite.getPosition().x + it->sprite.getLocalBounds().width < 0) {
                    it = obstacles.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        if (collision) {
            czywgrze = false;
        }
        if (collision && flag && prze.gra) {
            fifoQueue.push(pkt);
            if (fifoQueue.size() > maxSize) {
                fifoQueue.pop();
            }
            flag = false;
        }
        if (jump && !collision)
        {
            dinosaur.move(0, -gravity);
            gravity -= 0.2f;
            if (dinosaur.getPosition().y >= 298)
            {
                jump = false;
                gravity = 10.0f;
                dinosaur.setPosition(dinosaur.getPosition().x, 298);
            }
        }
        else if (!collision)
        {
            if (dinosaur.getPosition().y < 298)
            {
                dinosaur.move(0, gravity);
                gravity += 0.2f;
            }
        }
        int x = window.getSize().y - dinosaur.getGlobalBounds().height - 50;
        for (const auto& obstacle : obstacles) {
            if (dinosaur.getGlobalBounds().intersects(obstacle.sprite.getGlobalBounds()) && !collision) {
                collision = true;
            }
        }
        tekstPunktow.setString("Score: " + std::to_string(pkt));
        wynikijeden.setString("Score   1: " + std::to_string(arr[9]));
        wynikidwa.setString("Score   2: " + std::to_string(arr[8]));
        wynikitrzy.setString("Score   3: " + std::to_string(arr[7]));
        wynikicztery.setString("Score   4: " + std::to_string(arr[6]));
        wynikipienc.setString("Score   5: " + std::to_string(arr[5]));
        wynikiszesc.setString("Score   6: " + std::to_string(arr[4]));
        wynikisiedem.setString("Score   7: " + std::to_string(arr[3]));
        wynikiosiem.setString("Score   8: " + std::to_string(arr[2]));
        wynikidziew.setString("Score   9: " + std::to_string(arr[1]));
        wynikidziesienc.setString("Score 10: " + std::to_string(arr[0]));
        window.clear(sf::Color::White);
        if (prze.tablica) {
            window.draw(wyniki);
            window.draw(wynikijeden);
            window.draw(wynikidwa);
            window.draw(wynikitrzy);
            window.draw(wynikicztery);
            window.draw(wynikipienc);
            window.draw(wynikiszesc);
            window.draw(wynikisiedem);
            window.draw(wynikiosiem);
            window.draw(wynikidziew);
            window.draw(wynikidziesienc);
        }
        if (prze.menu)
        {
            window.draw(logo);
            window.draw(options);
        }
        if (prze.gra)
        {
         window.draw(backgroundSprite1);
         window.draw(backgroundSprite2);
        window.draw(backgroundSprite3);
        window.draw(backgroundSprite4);
        window.draw(duchkrz);
        window.draw(duchkrza);
         window.draw(backgroundSprite7);
         window.draw(backgroundSprite8);
        window.draw(backgroundSprite5);
       window.draw(backgroundSprite6);
        window.draw(backgroundSprite11);
         window.draw(backgroundSprite12);
        window.draw(backgroundSprite9);
        window.draw(backgroundSprite10);
            for (auto& obstacle : obstacles) {
                int textureIndex = obstacle.textureIndex;
                if (textureIndex == 0) {
                    obstacle.sprite.setTexture(obstacleTexture);
                }
                else {
                    obstacle.sprite.setTexture(obstacleTexture2);
                }
                window.draw(obstacle.sprite);
            }
            window.draw(tekstPunktow);
            window.draw(dinosaur);
            if (collision) { window.draw(text); }
        }
        window.draw(tut);
        window.display();
        sf::sleep(sf::seconds(0.002f));
    }
    saveQueueToFile(fifoQueue, "score.txt");
    while (!fifoQueue.empty()) {
        int element = fifoQueue.front();
        fifoQueue.pop();
    }
    return 0;
}
