// Copyright 2025 chrisfantasy

#include "Game/logic.hpp"
#include <chrono>

#include "Engine/Graphics/AssetManager.hpp"


using namespace std::chrono_literals;

typedef std::chrono::steady_clock::time_point current_time;
typedef std::chrono::seconds seconds;
typedef std::chrono::duration<double> timer;

namespace TR {

Game_States::Game_States() {
    characterMapping();
}
Game_States::~Game_States() {}


void Game_States::update(Engine::Engine* gEngine, Sprite_Map& sprite_set, Player_Set& player_set) {}

void Game_States::characterMapping() {
    _char_map.insert({ 
        /* Punctuation and Other Symbols */
        {' ', Engine::Vector2i(0, 0)},
        {'•', Engine::Vector2i(34, 0)},
        {',', Engine::Vector2i(51, 0)},
        {'.', Engine::Vector2i(68, 0)},
        {'·', Engine::Vector2i(85, 0)},
        {':', Engine::Vector2i(102, 0)},
        {';', Engine::Vector2i(119, 0)},
        {'?', Engine::Vector2i(136, 0)},
        {'!', Engine::Vector2i(153, 0)},
        {'"', Engine::Vector2i(170, 0)},
        {'º', Engine::Vector2i(187, 0)},
        {'\'', Engine::Vector2i(204, 0)},
        {'`', Engine::Vector2i(221, 0)},
        {'‴', Engine::Vector2i(238, 0)},
        {'^', Engine::Vector2i(255, 0)},
        {'–', Engine::Vector2i(0, 17)},
        {'_', Engine::Vector2i(17, 17)},
        {'‘', Engine::Vector2i(85, 34)},
        {'’', Engine::Vector2i(102, 34)},
        {'“', Engine::Vector2i(119, 34)},
        {'”', Engine::Vector2i(136, 34)},
        {'(', Engine::Vector2i(153, 34)},
        {')', Engine::Vector2i(170, 34)},
        {'[', Engine::Vector2i(221, 34)},
        {']', Engine::Vector2i(238, 34)},

        /* Numbers */
        {'0', Engine::Vector2i(187, 204)},
        {'1', Engine::Vector2i(204, 204)},
        {'2', Engine::Vector2i(221, 204)},
        {'3', Engine::Vector2i(238, 204)},
        {'4', Engine::Vector2i(255, 204)},
        {'5', Engine::Vector2i(0, 221)},
        {'6', Engine::Vector2i(17, 221)},
        {'7', Engine::Vector2i(34, 221)},
        {'8', Engine::Vector2i(51, 221)},
        {'9', Engine::Vector2i(68, 221)},

        /* Uppercase Letters */
        {'A', Engine::Vector2i(204, 221)},
        {'B', Engine::Vector2i(221, 221)},
        {'C', Engine::Vector2i(238, 221)},
        {'D', Engine::Vector2i(255, 221)},
        {'E', Engine::Vector2i(0, 238)},
        {'F', Engine::Vector2i(17, 238)},
        {'G', Engine::Vector2i(34, 238)},
        {'H', Engine::Vector2i(51, 238)},
        {'I', Engine::Vector2i(68, 238)},
        {'J', Engine::Vector2i(85, 238)},
        {'K', Engine::Vector2i(102, 238)},
        {'L', Engine::Vector2i(119, 238)},
        {'M', Engine::Vector2i(136, 238)},
        {'N', Engine::Vector2i(153, 238)},
        {'O', Engine::Vector2i(170, 238)},
        {'P', Engine::Vector2i(187, 238)},
        {'Q', Engine::Vector2i(204, 238)},
        {'R', Engine::Vector2i(221, 238)},
        {'S', Engine::Vector2i(238, 238)},
        {'T', Engine::Vector2i(255, 238)},
        {'U', Engine::Vector2i(0, 255)},
        {'V', Engine::Vector2i(17, 255)},
        {'W', Engine::Vector2i(34, 255)},
        {'X', Engine::Vector2i(51, 255)},
        {'Y', Engine::Vector2i(68, 255)},
        {'Z', Engine::Vector2i(85, 255)},

        /* Lowercase Letters */
        {'a', Engine::Vector2i(204, 255)},
        {'b', Engine::Vector2i(221, 255)},
        {'c', Engine::Vector2i(238, 255)},
        {'d', Engine::Vector2i(255, 255)},
        {'e', Engine::Vector2i(0, 272)},
        {'f', Engine::Vector2i(17, 272)},
        {'g', Engine::Vector2i(34, 272)},
        {'h', Engine::Vector2i(51, 272)},
        {'i', Engine::Vector2i(68, 272)},
        {'j', Engine::Vector2i(85, 272)},
        {'k', Engine::Vector2i(102, 272)},
        {'l', Engine::Vector2i(119, 272)},
        {'m', Engine::Vector2i(136, 272)},
        {'n', Engine::Vector2i(153, 272)},
        {'o', Engine::Vector2i(170, 272)},
        {'p', Engine::Vector2i(187, 272)},
        {'q', Engine::Vector2i(204, 272)},
        {'r', Engine::Vector2i(221, 272)},
        {'s', Engine::Vector2i(238, 272)},
        {'t', Engine::Vector2i(255, 272)},
        {'u', Engine::Vector2i(0, 289)},
        {'v', Engine::Vector2i(17, 289)},
        {'w', Engine::Vector2i(34, 289)},
        {'x', Engine::Vector2i(51, 289)},
        {'y', Engine::Vector2i(68, 289)},
        {'z', Engine::Vector2i(85, 289)},

        });
}

}  // namespace TR
