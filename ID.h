//
// Created by Jairo Borba on 10/31/21.
//
#ifndef JCVPLOT_ID_H
#define JCVPLOT_ID_H
#include <string>
namespace jcvplot {
    class ID {
    private:
        std::string m_label;
        std::string m_description;
    public:
        ID() = default;

        ID(
                const std::string &label,
                const std::string &description) :
                m_label(label), m_description(description) {
        }

        virtual ~ID() {}

        void setLabel(const std::string &label) { m_label = label; }

        void setDescription(const std::string &description) { m_description = description; }

        const std::string label() const { return m_label; }

        const std::string description() const { return m_description; }
    };
}
#endif //JCVPLOT_ID_H
