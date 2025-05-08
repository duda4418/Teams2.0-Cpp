#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <QTextEdit>

class Message {
public:
    Message(const std::string& senderId, const std::string& content, long timestamp)
        : m_senderId(senderId), m_content(content), m_timestamp(timestamp) {
    }

    virtual ~Message() {}

    // Pure virtual function that must be implemented by derived classes
    virtual void display(QTextEdit* chatDisplay) const = 0;

    // Getters
    std::string getSenderId() const { return m_senderId; }
    std::string getContent() const { return m_content; }
    long getTimestamp() const { return m_timestamp; }

protected:
    std::string m_senderId;
    std::string m_content;
    long m_timestamp;
};

class SentMessage : public Message {
public:
    SentMessage(const std::string& senderId, const std::string& content, long timestamp)
        : Message(senderId, content, timestamp) {
    }

    // Implementation of the display method for sent messages
    void display(QTextEdit* chatDisplay) const override {
        chatDisplay->append("You: " + QString::fromStdString(m_content));
    }
};

class ReceivedMessage : public Message {
public:
    ReceivedMessage(const std::string& senderId, const std::string& content, long timestamp, const std::string& senderName)
        : Message(senderId, content, timestamp), m_senderName(senderName) {
    }

    // Implementation of the display method for received messages
    void display(QTextEdit* chatDisplay) const override {
        chatDisplay->append(QString::fromStdString(m_senderName + ": " + m_content));
    }

private:
    std::string m_senderName;
};

#endif // MESSAGE_H