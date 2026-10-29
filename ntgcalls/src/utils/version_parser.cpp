//
// Created by Lauren on 13/10/24.
//

#include <ntgcalls/utils/version_parser.hpp>
#include <charconv>
#include <sstream>
#include <string>
#include <vector>

namespace ntgcalls::utils {
    VersionParser VersionParser::parse(const std::string& version) {
        try {
            std::vector<std::string> parts;
            size_t start = 0;
            while (start < version.size()) {
                const size_t dot = version.find('.', start);
                if (dot == std::string::npos) {
                    parts.push_back(version.substr(start));
                    break;
                }
                parts.push_back(version.substr(start, dot - start));
                start = dot + 1;
            }
            if (parts.size() != 3) {
                return {};
            }
            int nums[3] = {0, 0, 0};
            for (int i = 0; i < 3; ++i) {
                const auto res = std::from_chars(parts[i].data(), parts[i].data() + parts[i].size(), nums[i]);
                if (res.ec != std::errc()) {
                    return {};
                }
            }
            return {nums[0], nums[1], nums[2]};
        } catch (const std::invalid_argument&) {
            return {};
        }
    }

    bool VersionParser::operator>=(const VersionParser& other) {
        return std::tie(major, minor, micro) >= std::tie(other.major, other.minor, other.micro);
    }

    bool VersionParser::operator<=(const VersionParser& other) {
        return std::tie(major, minor, micro) <= std::tie(other.major, other.minor, other.micro);
    }

    bool VersionParser::operator<(const VersionParser& other) {
        return std::tie(major, minor, micro) < std::tie(other.major, other.minor, other.micro);
    }

    bool VersionParser::operator>(const VersionParser& other) {
        return std::tie(major, minor, micro) > std::tie(other.major, other.minor, other.micro);
    }

    bool VersionParser::operator==(const VersionParser& other) {
        return std::tie(major, minor, micro) == std::tie(other.major, other.minor, other.micro);
    }

    std::string VersionParser::to_string() const {
        return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(micro);
    }
} // ntgcalls::utils
