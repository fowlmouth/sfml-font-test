#include <SFML/Graphics.hpp>
#include <iostream>

void draw_ui(sf::RenderTarget& target, sf::Font& font, int max_y)
{
  sf::Vector2f position{10,10};
  int characer_size = 24;
  sf::Text text;
  text.setFont(font);
  text.setString("The quick brown fox jumped over your mom");
  text.setFillColor(sf::Color::White);
  while(position.y < max_y)
  {
    text.setPosition(position);
    text.setCharacterSize(characer_size);
    target.draw(text);
    position.y += std::floor(text.getLocalBounds().height + 4.5f);
    characer_size += 12;
  }
}

int main(int argc, const char** argv)
{
  const char* font_path = "OpenSans-Regular.ttf";
  if(argc == 2)
  {
    font_path = argv[1];
  }

  sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
  sf::Font ui_font;
  if(!ui_font.loadFromFile(font_path))
  {
    std::cerr << "Failed to open font path= " << font_path << std::endl;
    return 1;
  }

  sf::RenderTexture ui_texture;
  ui_texture.create(window.getSize().x, window.getSize().y);

  int render_mode = 0; // 1 is render texture mode

  while (window.isOpen())
  {

    sf::Event event;

    while (window.pollEvent(event))
    {
      switch(event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::Resized:
        ui_texture.create(event.size.width, event.size.height);
        break;
      case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Key::Space)
        {
          render_mode = (render_mode + 1) & 1;
          std::cout << "render mode: " << render_mode << std::endl;
        }
        break;
      default:
        break;
      }
    }

    window.clear();

    sf::RenderTarget* target = &window;
    if(render_mode == 1)
    {
      target = &ui_texture;
      ui_texture.clear(sf::Color::Transparent);
    }

    draw_ui(*target, ui_font, window.getSize().y);

    if(render_mode == 1)
    {
      ui_texture.display();
      sf::Sprite sprite(ui_texture.getTexture());
      window.draw(sprite);
    }

    window.display();
  }

  return 0;

}
