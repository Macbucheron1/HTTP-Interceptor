// ============================================================================
// test_isValidUrl.cpp
// Tests unitaires de la fonctionnalité isValidUrl à l’aide de Catch2.
//
// Chaque test couvre un ensemble de cas simples, limites et erronés.
// Permet de garantir la fiabilité du module concerné.
// ============================================================================


#include <catch2/catch_all.hpp>
#include "../includes/Utils.hpp"

TEST_CASE("URL valides simples", "[validation]") {
    REQUIRE(Utils::isValidURL("http://example.com"));
    REQUIRE(Utils::isValidURL("https://example.org"));
}

TEST_CASE("URL avec paramètres", "[validation]") {
    REQUIRE(Utils::isValidURL("https://site.com/path?x=1&y=2"));
    REQUIRE(Utils::isValidURL("http://localhost:8080/test?id=123"));
}

TEST_CASE("URL invalides évidentes", "[validation]") {
    REQUIRE_FALSE(Utils::isValidURL("not_a_url"));
    REQUIRE_FALSE(Utils::isValidURL("http//missing-colon.com"));
    REQUIRE_FALSE(Utils::isValidURL("example.com")); // pas de protocole
}

TEST_CASE("URL avec protocole non supporté", "[validation]") {
    REQUIRE_FALSE(Utils::isValidURL("ftp://example.com"));
    REQUIRE_FALSE(Utils::isValidURL("file:///etc/passwd"));
}

TEST_CASE("URL vide ou trop longue", "[validation]") {
    REQUIRE_FALSE(Utils::isValidURL(""));
    
    std::string long_url = "http://example.com/" + std::string(2048, 'a');
    REQUIRE_FALSE(Utils::isValidURL(long_url));
}
