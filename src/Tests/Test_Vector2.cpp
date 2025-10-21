#include <boost/test/unit_test.hpp>
#include "Engine/Math/Vector2.hpp"

BOOST_AUTO_TEST_SUITE(Vector2Tests)

BOOST_AUTO_TEST_CASE(Vector2_Constructor)
{
    Engine::Vector2 vec(1.0f, 2.0f);
    BOOST_CHECK_EQUAL(vec.x, 1.0f);
    BOOST_CHECK_EQUAL(vec.y, 2.0f);
}

BOOST_AUTO_TEST_CASE(Vector2_Addition)
{
    Engine::Vector2 vec1(1.0f, 2.0f);
    Engine::Vector2 vec2(3.0f, 4.0f);
    Engine::Vector2 result = vec1 + vec2;
    BOOST_CHECK_EQUAL(result.x, 4.0f);
    BOOST_CHECK_EQUAL(result.y, 6.0f);
}

BOOST_AUTO_TEST_CASE(Vector2_Subtraction)
{
    Engine::Vector2 vec1(5.0f, 6.0f);
    Engine::Vector2 vec2(3.0f, 4.0f);
    Engine::Vector2 result = vec1 - vec2;
    BOOST_CHECK_EQUAL(result.x, 2.0f);
    BOOST_CHECK_EQUAL(result.y, 2.0f);
}

BOOST_AUTO_TEST_SUITE_END()
