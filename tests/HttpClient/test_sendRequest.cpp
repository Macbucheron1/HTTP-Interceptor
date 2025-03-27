// ============================================================================
// test_sendRequest.cpp
// Tests unitaires pour HttpClient::sendRequest()
// ============================================================================

#include <catch2/catch_all.hpp>
#include "../../includes/HttpClient.hpp"

TEST_CASE("HttpClient::sendRequest - tests complets", "[HttpClient][sendRequest]") {

    SECTION("GET vers un domaine valide (httpbin.org)") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://httpbin.org/get");
        REQUIRE(res.status_code == 200);
        REQUIRE(res.body.find("\"url\": \"http://httpbin.org/get\"") != std::string::npos);
    }

    SECTION("Requête vers un domaine inexistant") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://nonexistent.local");
        REQUIRE(res.status_code == 0); // ou code d'erreur maison
        REQUIRE(!res.error.empty());  // Le champ error doit contenir quelque chose
    }

    SECTION("Requête vers une IP non routable (timeout simulé)") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://10.255.255.1", "GET");
        REQUIRE(res.status_code == 0);
        REQUIRE(!res.error.empty());
    }

    SECTION("Réponse HTTP 404") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://httpbin.org/status/404");
        REQUIRE(res.status_code == 404);
    }

    SECTION("Réponse vide") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://httpbin.org/status/204"); // 204 No Content
        REQUIRE(res.status_code == 204);
        REQUIRE(res.body.empty());
    }

    SECTION("Méthode non supportée (OPTIONS)") {
        HttpClient::HttpResponse res = HttpClient::sendRequest("http://httpbin.org/anything", "OPTIONS");
        REQUIRE(res.status_code >= 200);
    }

}
