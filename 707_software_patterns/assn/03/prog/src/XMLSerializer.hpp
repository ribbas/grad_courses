#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"

class XMLSerializer {
private:
    int indentationLevel;
    std::fstream file;

    virtual void prettyIndentation();

public:
    XMLSerializer(const std::string& filename)
        : indentationLevel(0), file(filename.c_str(), std::ios_base::out) {}
    ~XMLSerializer() {}

    virtual void serializePretty(dom::Node*);
    virtual void serializeMinimal(dom::Node*);
};

template <typename U>
class XMLSerializerIterator {
public:
    typedef typename std::vector<dom::Node*>::iterator iter_type;
    XMLSerializerIterator(U* p_data) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void begin() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void next() {
        m_it_++;
    }

    bool end() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    XMLSerializerIterator* operator++() {
        XMLSerializerIterator* temp;
        temp->m_it_ = m_it_++;
        return temp;
    }

    // explicit iter_type operator*() const {
    //     return *m_it_;
    // }

    iter_type Current() {
        return m_it_;
    }

private:
    U* m_p_data_;
    iter_type m_it_;
};

/**
 * Generic Collections/Containers provides one or several methods for retrieving
 * fresh iterator instances, compatible with the collection class.
 */

class DocumentContainer {
    friend class XMLSerializerIterator<DocumentContainer>;

public:
    void containerize(dom::Node* document, bool init = true) {

        if (init) {
            m_data_.push_back(document);
            std::cout << "con " << document << std::endl;
        }

        if (document->hasChildNodes()) {
            for (auto i : *document->getChildNodes()) {
                std::cout << "con " << i << std::endl;
                m_data_.push_back(i);
                containerize(i, false);
            }
        }
    }

    XMLSerializerIterator<DocumentContainer>* CreateIterator() {
        return new XMLSerializerIterator<DocumentContainer>(this);
    }

private:
    std::vector<dom::Node*> m_data_;
};

#endif