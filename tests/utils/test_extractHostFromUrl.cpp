// ============================================================================
// test_extractHostFromUrl.cpp
// Tests unitaires pour la fonction Utils::extractHostFromURL()
// ============================================================================

#include <catch2/catch_all.hpp>
#include "../../includes/Utils.hpp"

TEST_CASE("extractHostFromURL - tests complets", "[Utils][extractHostFromURL]") {

    SECTION("URLs simples") {
        REQUIRE(Utils::extractHostFromURL("http://example.com") == "example.com");
        REQUIRE(Utils::extractHostFromURL("https://example.org") == "example.org");
    }

    SECTION("URLs avec chemin ou paramètres") {
        REQUIRE(Utils::extractHostFromURL("http://example.com/test/page") == "example.com");
        REQUIRE(Utils::extractHostFromURL("https://site.com?token=abc") == "site.com");
        REQUIRE(Utils::extractHostFromURL("https://domain.com/path?query=1") == "domain.com");
    }

    SECTION("URLs avec port") {
        REQUIRE(Utils::extractHostFromURL("http://example.com:8080") == "example.com");
        REQUIRE(Utils::extractHostFromURL("https://secure.org:443/page") == "secure.org");
    }

    SECTION("Sous-domaines") {
        REQUIRE(Utils::extractHostFromURL("http://sub.domain.net/path") == "sub.domain.net");
    }

    SECTION("IPs (IPv4)") {
        REQUIRE(Utils::extractHostFromURL("http://192.168.0.1/home") == "192.168.0.1");
        REQUIRE(Utils::extractHostFromURL("http://192.168.0.1:3000") == "192.168.0.1");
    }

    SECTION("IPv6") {
        REQUIRE(Utils::extractHostFromURL("http://[2001:db8::1]/home") == "[2001:db8::1]");
    }

    SECTION("Cas ambigus ou malformés") {
        REQUIRE(Utils::extractHostFromURL("example.com") == "example.com"); // si tu l'acceptes
        REQUIRE(Utils::extractHostFromURL("") == "");
        REQUIRE(Utils::extractHostFromURL("http://") == "");
    }
}
