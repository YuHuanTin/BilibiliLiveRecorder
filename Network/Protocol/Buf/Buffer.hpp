#ifndef LIBSUPERCPP4WIN_BUFFER_HPP
#define LIBSUPERCPP4WIN_BUFFER_HPP


#include <cstddef>
#include <iterator>
#include <stdexcept>


/**
 * һ���洢 T ���͵Ŀɶ���д Buffer ��
 * @tparam T 
 */
template<typename T>
class Buffer {
private:

    /**
     * ��� ��ǰλ�� + CheckType * ElementCount �Ƿ񳬳������λ�ã�Ĭ��Ϊ T ����
     * @tparam CheckType 
     * @param ElementCount 
     * @return 
     */
    template<typename CheckType = T>
    constexpr void check_out_of_range(size_t ElementCount) const {
        if (m_currentPostion + ElementCount * sizeof(CheckType) > m_maxPostion) throw std::runtime_error("out of range");
    }

public:
    Buffer() = delete;

    constexpr Buffer(T *Begin, T *End) : Buffer(Begin, std::advance(Begin, End)) {}

    constexpr Buffer(T *Ptr, size_t Count) : m_buffer(Ptr), m_maxPostion(Count) {}

    Buffer &operator=(const Buffer &Right) {
        if (&Right == this) {
            return *this;
        }

        m_buffer = Right.m_buffer;
        m_currentPostion = Right.m_currentPostion;
        m_maxPostion = Right.m_maxPostion;
        return *this;
    }

    Buffer &operator=(Buffer &&Right) noexcept {
        if (&Right == this) {
            return *this;
        }

        m_buffer = Right.m_buffer;
        m_currentPostion = Right.m_currentPostion;
        m_maxPostion = Right.m_maxPostion;

        Right.m_buffer = nullptr;
        Right.m_currentPostion = 0;
        Right.m_maxPostion = 0;
        return *this;
    }

    [[nodiscard]] constexpr size_t getCurrnetPos() const noexcept {
        return m_currentPostion;
    }

    [[nodiscard]] constexpr size_t getMaxPos() const noexcept {
        return m_maxPostion;
    }

    /**
     * ��ȡ��ǰλ�õ� T Ԫ��
     * @return 
     */
    constexpr T &getCurrentElement() const {
        check_out_of_range(1);

        return *reinterpret_cast<T *>(m_buffer + m_currentPostion);
    }

    /**
     * �ӵ�ǰλ�ö�ȡһ�� ReadType Ԫ��
     * @tparam ReadType 
     * @return 
     */
    template<typename ReadType>
    constexpr ReadType read() {
        check_out_of_range<ReadType>(1);

        auto *readTypePtr = reinterpret_cast<ReadType *>(m_buffer + m_currentPostion);
        next<uint8_t>(sizeof(ReadType));
        return *readTypePtr;
    }

    /**
     * ��ȡ ElementCount ��Ԫ�ص� Ptr Ϊ��ʼ��ַ�Ŀռ�
     * @tparam ElementCount 
     * @param Ptr 
     * @return 
     */
    template<size_t ElementCount>
    constexpr void read(T *Ptr) {
        read(Ptr, ElementCount);
    }

    /**
     * ��ȡ ElementCount ��Ԫ�ص� Ptr Ϊ��ʼ��ַ�Ŀռ�
     * @param Ptr 
     * @param ElementCount 
     * @return 
     */
    constexpr void read(T *Ptr, size_t ElementCount) {
        check_out_of_range(ElementCount);

        std::copy(m_buffer + m_currentPostion, m_buffer + m_currentPostion + ElementCount * sizeof(T), Ptr);
        next(ElementCount);
    }

    /**
     * �ڵ�ǰλ��д�� WriteType ���͵�ֵ
     * @tparam WriteType 
     * @param WriteValue 
     */
    template<typename WriteType>
    void write(WriteType &&WriteValue) {
        check_out_of_range<WriteType>(1);

        auto *writeTypePtr = reinterpret_cast<std::remove_reference_t<WriteType> * >(m_buffer + m_currentPostion);
        *writeTypePtr = WriteValue;
        next<WriteType>(1);
    }

    template<typename WriteType>
    void write(WriteType *Ptr, size_t Count) {
        check_out_of_range<WriteType>(Count);

        std::copy(Ptr, Ptr + Count, m_buffer + m_currentPostion);
        next<WriteType>(Count);
    }

    template<typename WriteType>
    void write(WriteType *Begin, WriteType *End) {
        write(Begin, std::advance(Begin, End));
    }

    /**
     * ��ǰ�ƶ�ָ�룬Ĭ���ƶ� Count �� T ���͵�λ�ã���Ϊ Count �� PrevType ���͵�λ��
     * @tparam PrevType 
     * @param Count 
     * @return 
     */
    template<typename PrevType = T>
    constexpr void prev(size_t Count) noexcept {
        m_currentPostion -= Count * sizeof(PrevType);
    }

    /**
     * ����ƶ�ָ�룬Ĭ���ƶ� Count �� T ���͵�λ�ã���Ϊ Count �� NextType ���͵�λ��
     * @tparam NextType 
     * @param Count 
     * @return 
     */
    template<typename NextType = T>
    constexpr void next(size_t Count) noexcept {
        m_currentPostion += Count * sizeof(NextType);
    }

    constexpr void moveTo(size_t Pos) noexcept {
        m_currentPostion = Pos;
    }

    constexpr void reset() noexcept {
        m_currentPostion = 0;
    }

    [[nodiscard]] constexpr bool eof() const {
        return m_currentPostion >= m_maxPostion;
    }

private:
    T *m_buffer = nullptr;
    size_t m_currentPostion = 0;
    size_t m_maxPostion = 0;
};

#endif //LIBSUPERCPP4WIN_BUFFER_HPP
