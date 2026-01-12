#include "Game/logic_obj.hpp"
#include "Engine/Graphics/AssetManager.hpp"

namespace TR {

    TextBox::TextBox() : Scene_Object(), _text_stored("Test Message"), _text_current(""), _text_speed(1)
        , _confirm_prompt(false), _text_attr{ TXT_NULL }, _text_gfx(Engine::Text("", 40)) {
    }

    TextBox::TextBox(const char* text, bool prompt) : Scene_Object(), _text_stored(text), _text_current(""), _text_speed(3)
        , _confirm_prompt(prompt), _text_attr{ TXT_NULL }, _text_gfx(Engine::Text(_text_current.c_str(), 40)) {
    }

    TextBox::TextBox(const char* text, bool prompt, uint16_t transitions) : TextBox(text, prompt) {
        _text_attr = transitions;
    }

    TextBox::~TextBox() {
        TTF_Quit();
    }

    void TextBox::init(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {

        /* Initialize the TTF library */
        if (!TTF_Init()) {
            SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        }

        /* Creating Mask Area*/
        _sprite_mask = Engine::Recti(Engine::Vector2i(120, 160) * SCREEN_SCALE, Engine::Vector2i(400, 200) * SCREEN_SCALE);

        /* Texture Initialization */

        gEngine->getAssetManager()->loadTexture("assets/gfx/sprites/Common/Placeholder_Box.png", "TEXT_BOX", renderer);
        gEngine->getAssetManager()->storeTexture(_text_gfx.load(renderer, Engine::Recti{ 0, 0, 370 * SCREEN_SCALE, 200 * SCREEN_SCALE}), "TEXT", renderer);

        /* Sprite Creation */


        sprite_set.insert({ "Text_Box",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT_BOX"), 400, 200) });
        sprite_set.insert({ "Text",
            std::make_unique<Engine::Sprite>(gEngine->getAssetManager()->getTexture("TEXT"), _text_gfx.getRenderSize().size.x, _text_gfx.getRenderSize().size.y)});
        sprite_set.at("Text_Box")->setSizeScale(SCREEN_SCALE);
        sprite_set.at("Text")->setSizeScale(SCREEN_SCALE);

        /* Update Position (Starts Off Screen) */
        _sprite_mask.position.x = 120 * SCREEN_SCALE;
        _sprite_mask.position.y = gEngine->getWindow()->getHeight();
        this->updateMask(sprite_set);

    }

    void TextBox::draw(SDL_Renderer* renderer, Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        // Set Postition
        this->updateMask(sprite_set);

        // Textbox
        sprite_set.at("Text_Box")->draw(renderer);

        // Text
        _text_gfx.setText(_text_current.c_str());

        gEngine->getAssetManager()->storeTexture(_text_gfx.load(renderer, Engine::Recti{ 0, 0, 370 * SCREEN_SCALE, 200 * SCREEN_SCALE }), "TEXT", renderer);
        sprite_set.at("Text")->swapTexture(gEngine->getAssetManager()->getTexture("TEXT"), _text_gfx.getRenderSize().size.x, _text_gfx.getRenderSize().size.y);
        sprite_set.at("Text")->draw(renderer);

    }

    void TextBox::updateMask(Sprite_Map& sprite_set) {
        sprite_set.at("Text_Box")->setPos(Engine::Vector2f(static_cast<float>(_sprite_mask.position.x), static_cast<float>(_sprite_mask.position.y)));
        sprite_set.at("Text")->setPos(Engine::Vector2f(static_cast<float>(_sprite_mask.position.x + (20.0 * SCREEN_SCALE)), 
            static_cast<float>(_sprite_mask.position.y + (20.0 * SCREEN_SCALE))));
    }

    void TextBox::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        this->objInput(gEngine, sprite_set, player_set);
        this->objMouseClick(gEngine, sprite_set, player_set);
        this->objMouseMove(gEngine, sprite_set, player_set);
        this->displayTextBox(gEngine);
    }

    void TextBox::objMouseMove(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}
    void TextBox::objMouseClick(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}

    void TextBox::objKeyInput(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {
        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_U)) {
            _text_attr |= TXT_ACTIVE;
        }
        if (gEngine->getInput()->isKeyPressed(SDL_SCANCODE_I)) {
            _text_attr |= TXT_ACTIVE;
        }

    }

    void TextBox::displayTextBox(Engine::Engine* gEngine) {

        if (_text_attr & TXT_ACTIVE) {
            // Text Entrance Transitions
            if (_text_attr & TXT_ENTER_EXIT) {
                if (_sprite_mask.position.x > 120 * SCREEN_SCALE || _sprite_mask.position.y > 160 * SCREEN_SCALE) {
                    if (_text_attr & TXT_UP_DOWN) {
                        if (_sprite_mask.position.y - 160 * SCREEN_SCALE < 16 * SCREEN_SCALE) {
                            _sprite_mask.position.y = 160 * SCREEN_SCALE;
                        }
                        else {
                            _sprite_mask.position.y -= 16 * SCREEN_SCALE;
                        }
                    }
                    if (_text_attr & TXT_LEFT_RIGHT) {
                        if (_sprite_mask.position.x - 120 * SCREEN_SCALE < 16 * SCREEN_SCALE) {
                            _sprite_mask.position.x = 120 * SCREEN_SCALE;
                        }
                        else {
                            _sprite_mask.position.x -= 16 * SCREEN_SCALE;
                        }
                    }
                }
                else {
                    _text_attr ^= TXT_ACTIVE;
                }
            }
            // Text Exit Transitions
            else if (_text_attr & ~TXT_ENTER_EXIT) {
                if ((_sprite_mask.position.y < gEngine->getWindow()->getHeight()) && (_text_attr & TXT_UP_DOWN)) {
                    _sprite_mask.position.y += 16 * SCREEN_SCALE;
                }
                else if ((_sprite_mask.position.x < gEngine->getWindow()->getWidth()) && (_text_attr & TXT_LEFT_RIGHT)) {
                    _sprite_mask.position.x += 16 * SCREEN_SCALE;
                }
                else {
                    _text_attr ^= TXT_ACTIVE;
                }
            }
        }
        
        // Text On Default
        else {
            if ((_sprite_mask.position.x == 120 * SCREEN_SCALE) && (_sprite_mask.position.y == 160 * SCREEN_SCALE)) {
                if (_text_current.size() < _text_stored.size()) {
                    _text_attr |= TXT_ACTIVE_TEXT;
                }
                else {
                    if (_text_attr & TXT_ACTIVE_TEXT) {
                        _text_attr ^= TXT_ACTIVE_TEXT;
                    }
                    _text_attr |= TXT_ACTIVE_TEXT_COMPLETE;
                }

                if (_text_attr & TXT_ACTIVE_TEXT) {
                    textAppear();
                }
                if (_text_attr & TXT_ACTIVE_TEXT_COMPLETE) {
                    _text_current = _text_stored;
                }
                
            }
        }
    }

    void TextBox::textAppear() {
        if (_time % ((4 - _text_speed) * 10) == 0) {
            _text_current.append(_text_stored, _text_current.size(), 1);
            if (_time >= 60) {
                _time = 0;
            }
        }
        if (_text_current.size() == _text_stored.size()) {
            _time++;
        }
    }

    void TextBox::textContinue() {}
}