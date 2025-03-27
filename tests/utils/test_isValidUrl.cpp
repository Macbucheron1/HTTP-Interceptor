// ============================================================================
// test_isValidUrl.cpp
// Tests unitaires de la fonction Utils::isValidURL()
// ============================================================================

#include <catch2/catch_all.hpp>
#include "../../includes/Utils.hpp"

TEST_CASE("isValidURL - tests complets", "[Utils][isValidURL]") {

    SECTION("URL valides simples") {
        REQUIRE(Utils::isValidURL("http://example.com"));
        REQUIRE(Utils::isValidURL("https://example.org"));
    }

    SECTION("URL avec paramètres") {
        REQUIRE(Utils::isValidURL("https://site.com/path?x=1&y=2"));
        REQUIRE(Utils::isValidURL("http://localhost:8080/test?id=123"));
    }

    SECTION("URL invalides évidentes") {
        REQUIRE_FALSE(Utils::isValidURL("not_a_url"));
        REQUIRE_FALSE(Utils::isValidURL("http//missing-colon.com"));
        REQUIRE_FALSE(Utils::isValidURL("example.com")); // pas de protocole
    }

    SECTION("URL avec protocole non supporté") {
        REQUIRE_FALSE(Utils::isValidURL("ftp://example.com"));
        REQUIRE_FALSE(Utils::isValidURL("file:///etc/passwd"));
    }

    SECTION("URL vide ou trop longue") {
        REQUIRE_FALSE(Utils::isValidURL(""));

        std::string long_url = "http://example.com/" + std::string(2048, 'a');
        REQUIRE_FALSE(Utils::isValidURL(long_url));
    }

}
