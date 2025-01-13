#include "TextureDisplay.h"
#include "BaseRunner.h"

TextureDisplay::TextureDisplay()
{
}

TextureDisplay::~TextureDisplay()
{
}

void TextureDisplay::initialize()
{
    this->elapsedTime = sf::Time::Zero;
	this->position = sf::Vector2f(0.f, 0.f);

    // Stores the paths per iteration
    for (const auto& entry : filesystem::directory_iterator("Media/Streaming")) {
        if (entry.is_regular_file()) 
            filePaths.push_back(entry.path().string());
    }

    // Avoids reallocation
    textures.reserve(filePaths.size()); 

    cout << "Found " << filePaths.size() << " images in the folder." << endl;
}

void TextureDisplay::processInput()
{
}

void TextureDisplay::update(sf::Time deltaTime)
{
    this->elapsedTime += deltaTime;

    if (this->elapsedTime.asSeconds() >= this->TIME_TO_DISPLAY && this->currentSpriteIndex < this->filePaths.size()) {
        sf::Texture texture; 

        if (texture.loadFromFile(this->filePaths[currentSpriteIndex])) {
            this->textures.push_back(texture);  
            sf::Sprite sprite(this->textures.back());

            
            sprite.setScale(this->IMAGE_SIZE / static_cast<float>(this->textures.back().getSize().x),
                            this->IMAGE_SIZE / static_cast<float>(this->textures.back().getSize().y));

            sprite.setPosition(this->position);
            this->sprites.push_back(std::move(sprite));

            this->position.x += this->IMAGE_SIZE + this->SPACING;
            if (this->position.x + this->IMAGE_SIZE > BaseRunner::WINDOW_WIDTH) {
                this->position.x = 0.f;
                this->position.y += this->IMAGE_SIZE + this->SPACING;
            }

            this->currentSpriteIndex++;
        }

        else 
            cout << "Failed to load image: " << this->filePaths[this->currentSpriteIndex] << endl;

        this->elapsedTime = sf::Time::Zero;
    }
}

void TextureDisplay::draw(sf::RenderWindow* targetWindow)
{
    for (const auto& sprite : sprites) {
        targetWindow->draw(sprite);
    }
}