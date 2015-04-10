#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

struct HelloWorld {
    void operator()() const {
        std::cout << "Hello, World!" << std::endl;
    }
};

struct World {
    void operator()() const {
        std::cout << "World!" << std::endl;
    }
};

void print_args(float x, float y) {
    std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y)
{
    std::cout << "The sum is " << x + y << std::endl;
}

void print_product(float x, float y)
{
    std::cout << "The product is " << x * y << std::endl;
}

void print_difference(float x, float y)
{
    std::cout << "The difference is " << x - y << std::endl;
}

void print_quotient(float x, float y)
{
    std::cout << "The quotient is " << x / y << std::endl;
}

template<typename T>
struct maximum {
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        // If there are no slots to call, just return the
        //     // default-constructed value
        if(first == last ) return T();
        T max_value = *first++;
        while (first != last) {
            if (max_value < *first)
                max_value = *first;
            ++first;
        }
        return max_value;
    }
};

template<typename Container>
struct aggregate_values {
    typedef Container result_type;

    template<typename InputIterator>
    Container operator()(InputIterator first, InputIterator last) const {
        Container values;

        while(first != last) {
            values.push_back(*first);
            ++first;
        }
        return values;
    }
};

float product(float x, float y) {
    return x * y;
}
float quotient(float x, float y) {
    return x / y;
}
float sum(float x, float y) {
    return x + y;
}
float difference(float x, float y) {
    return x - y;
}

class NewsItem
{
public:
    NewsItem();

    NewsItem(const NewsItem& item)
    {
        msg = item.msg;
    }

    NewsItem(const std::string message)
    {
        msg = message;
    }

    const std::string text() const
    {
        return msg;
    }

private:
    std::string msg;
};

class MessageArea
{
public:
    MessageArea() {
        messageText = "default";
    }

    MessageArea(const MessageArea& messageArea)
    {
        messageText = messageArea.messageText;
    }

    MessageArea(const std::string  message)
    {
        messageText = message;
    }

    void update()
    {
        std::cout <<"messageText="<<messageText<<std::endl;
    }

    std::string messageText;
};

class NewsMessageArea : public MessageArea, public boost::signals2::trackable//trackable is important
{
public:
    NewsMessageArea(const std::string message):MessageArea(message) {}
    void displayNews(const NewsItem& news)
    {
        messageText = news.text();
        update();
    }
};

class Document
{
public:
    typedef boost::signals2::signal<void (bool)>  signal_t;
    typedef boost::signals2::connection  connection_t;

public:
    Document()
    {}

    connection_t connect(signal_t::slot_function_type subscriber)
    {
        return m_sig.connect(subscriber);
    }

    void disconnect(connection_t subscriber)
    {
        subscriber.disconnect();
    }

    void append(const char* s)
    {
        m_text += s;
        m_sig(true);
    }

    const std::string& getText() const
    {
        return m_text;
    }

private:
    signal_t    m_sig;
    std::string m_text;
};

class View
{
public:
    View(Document& m)
        : m_document(m)
    {
        m_connection = m_document.connect(boost::bind(&View::refresh, this, _1));
    }

    virtual ~View()
    {
        m_document.disconnect(m_connection);
    }

    virtual void refresh(bool bExtended) const = 0;

protected:
    Document&               m_document;

private:
    Document::connection_t  m_connection;
};

class TextView : public View
{
public:
    TextView(Document& doc)
        : View(doc)
    {}

    virtual void refresh(bool bExtended) const
    {
        std::cout << "TextView: " << m_document.getText() << std::endl;
    }
};

class HexView : public View
{
public:
    HexView(Document& doc)
        : View(doc)
    {}

    virtual void refresh(bool bExtended) const
    {
        const std::string&  s = m_document.getText();

        std::cout << "HexView:";

        for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
            std::cout << ' ' << std::hex << static_cast<int>(*it);

        std::cout << std::endl;
    }
};

int main(int argc, char* argv[])
{
    Document    doc;
    TextView    v1(doc);
    HexView     v2(doc);

    doc.append(argc == 2 ? argv[1] : "ÄãºÃ");
    return 0;
}

//int main() {
//    boost::signals2::signal<void (const NewsItem&) > deliverNews;
//    NewsMessageArea* newsMessageArea = new NewsMessageArea("Hello, World!");
//    deliverNews.connect(boost::bind(&NewsMessageArea::displayNews, newsMessageArea, _1));
//
//    const NewsItem newItem("Hello, Kitty!");
//    deliverNews(newItem);
//
//    delete newsMessageArea;
//    std::cout<<"*******Segmentation fault below if no trackable******"<<std::endl;
//    deliverNews(newItem);
////	 boost::signals2::signal<void ()> sig;
////
////	   // Connect a HelloWorld slot
////	     HelloWorld hello;
////	     sig.connect(hello);
////
////	boost::signals2::signal<void (float, float)> sig;
//
////	sig.connect(&print_args);
////	sig.connect(&print_sum);
////	sig.connect(&print_product);
////	sig.connect(&print_difference);
////	sig.connect(&print_quotient);
//
////	boost::signals2::signal<float (float x, float y),
////		              maximum<float> > sig;
////
////	sig.connect(&product);
////	sig.connect(&quotient);
////    sig.connect(&sum);
////    sig.connect(&difference);
//
////    boost::signals2::signal<float (float, float),
////          aggregate_values<std::vector<float> > > sig;
////    sig.connect(&quotient);
////    sig.connect(&product);
////    sig.connect(&sum);
////    sig.connect(&difference);
////
////    auto result = sig(5, 3);
////    std::for_each(result.begin(), result.end(), [](float c) {
////        printf("%lf ", c);
////    });
////    printf("\n");
////    sig.disconnect(&difference);
////    result = sig(5, 3);
////    std::for_each(result.begin(), result.end(), [](float c) {
////        printf("%lf ", c);
////    });
////    printf("\n");
////
////
////    boost::signals2::signal<void()> sig6;
////    sig6.connect(World());
////    boost::signals2::connection c = sig6.connect(HelloWorld());
////
////    if (c.connected()) {
////        sig6();
////    }
////    c.disconnect();
////    printf("%s\n", c.connected() ? "connected" : "disconnected");
////
////    sig6();
////
////    printf("------delemiter------\n");
////    boost::signals2::signal<void()> sig7;
////    auto c1 = sig7.connect(HelloWorld());
////    sig7.connect(World());
////    sig7();
////    {
////        boost::signals2::shared_connection_block block(c1);
////        sig7();
////        printf("%s\n", "c1 is blocked.");
////    }
////    printf("%s\n", c1.blocked() ? "blocked" : "not blocked");
////    sig7();
////
////    std::cout<<"***************connection management scoped**************"<<std::endl;
////    boost::signals2::signal<void ()> sig8;
////    {
////        boost::signals2::scoped_connection c2(sig8.connect(HelloWorld()));
////        sig8();
////        std::cout<<"c2 is blocked"<<std::endl;
////    }
////    printf("------\n");
////    sig8();
////
////    std::cout<<"***************connection management use shared_ptr**************"<<std::endl;
////    boost::signals2::signal<void ()> sig10;
////    {
////        boost::shared_ptr<World> w(new World());
////        sig10.connect(boost::bind(&World::operator(), w.get()));
////
////        std::cout <<"num of slots = "<< sig10.num_slots() << std::endl;
////    }
////
////    std::cout <<"num of slots = "<< sig10.num_slots() << std::endl;
////    sig10();
////
////    std::cout<<"***************connection management use trackable**************"<<std::endl;
////    boost::signals2::signal<void ()> sig11;
////    {
////        boost::shared_ptr<World> w(new World());
////        sig11.connect(boost::bind(&World::operator(), w.get()));
////    }
////
////    std::cout <<"num of slots = "<< sig11.num_slots() << std::endl;
////    sig11();
//
//    return 0;
//}
