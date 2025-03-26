// ============================================================================
// Utils.{hpp,cpp}
// Fonctions utilitaires générales utilisées dans tout le projet.
//
// Contient des helpers comme la validation d’URL, la sanitation des entrées,
// ou l’extraction de données depuis une chaîne (ex: host depuis une URL).
// ============================================================================

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

/**
 * @namespace Utils
 * 
 * @brief Regroupe les fonctions utilitaires générales du projet
 *        (ex : validation d’URL, extraction de données, sanitation).
 */
namespace Utils {

    /**
     * @brief Vérifie si l'URL fournie est considérée comme valide 
     *        (syntaxe, protocole supporté, etc.).
     * 
     * @param url 
     *   Chaîne de caractères représentant l'URL (ex: "http://example.com").
     * 
     * @return 
     *   true  si l'URL respecte les critères de validité,
     *   false sinon.
     */
    bool isValidURL(const std::string& url);

    /**
     * @brief Extrait l'hôte (nom de domaine ou adresse IP) depuis une URL.
     * 
     * @param url 
     *   Chaîne représentant l'URL (ex: "https://example.com:8080/path").
     * 
     * @return 
     *   Chaîne correspondant à l'hôte (ex: "example.com").
     *   Retourne une chaîne vide si extraction impossible.
     */
    std::string extractHostFromURL(const std::string& url);

    /**
     * @brief Nettoie/échappe la chaîne de caractères pour éviter d'éventuelles
     *        injections ou caractères dangereux.
     * 
     * @param input 
     *   La chaîne à assainir.
     * 
     * @return 
     *   La chaîne nettoyée, prête à être manipulée ou loggée en toute sécurité.
     */
    std::string sanitizeInput(const std::string& input);

} // namespace Utils

#endif // UTILS_HPP
