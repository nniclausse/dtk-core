// dtkCoreAsKeyValueRange.h
//

#pragma once

#include <utility>

namespace dtk {

    namespace core {

        namespace detail {

            template <typename ... T>
            using void_t = void;

            template <typename C, typename = void_t<>>
            struct has_container_key_value_iterator : std::false_type
            {
            };

            template <typename C>
            struct has_container_key_value_iterator<C,
                                                    void_t<decltype(std::declval<C &>().keyValueBegin())>
                                                    > : std::true_type
            {
            };

            template <typename C>
            using container_has_key_value_iterator = typename std::enable_if_t<has_container_key_value_iterator<C>::value, bool>;
        }

        template <typename C, typename E = detail::container_has_key_value_iterator<C>>
        class asKeyValueRange
        {
        public:
             asKeyValueRange(C &data) : m_data{data} {}
            ~asKeyValueRange(void) = default;

            auto begin(void) { return m_data.keyValueBegin(); }
            auto end(void) { return m_data.keyValueEnd(); }

            auto begin(void) const { return m_data.keyValueBegin(); }
            auto end(void) const { return m_data.keyValueEnd(); }

            auto cbegin(void) const { return m_data.constKeyValueBegin(); }
            auto cend(void) const { return m_data.constKeyValueEnd(); }

        private:
            C &m_data;
        };
    }
}

//
// dtkCoreAsKeyValueRange.h ends here
