#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
// 定义一个智能指针类型,用于管理ip::tcp::socket对象
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

int main() {
    boost::asio::io_service service; // 创建一个io_service对象 是所有I/O操作的基础

    // 创建一个TCP端点，监听IPv4的2001端口
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(),2001);

    // 创建一个acceptor对象，用于监听来自客户端的连接请求
    boost::asio::ip::tcp::acceptor acc(service,ep);

    // 无限循环等待客户端的连接
    while(true)
    {
        // 创建一个新的socket对象
        socket_ptr sock(new boost::asio::ip::tcp::socket(service));
        acc.accept(*sock); // 连接请求，并将转移到新创建的socket对象

        // 为每个客户端连接启动一个新的线程，并在线程中处理连接
        boost::thread(boost::bind(client_session,sock));
    }
    return 0;
}
// 定义一个函数来处理客户端会话
void client_session(socket_ptr sock)
{
    // 无限循环 读取客户端发送的数据来响应
    while(true)
    {
        char data[512]; // 创建一个缓冲区来存储接收到的数据
        size_t len = sock->read_some(boost::asio::buffer(data)); // 从sock读取一些数据

        if(len > 0) // 如果成功读取数据
        {
            boost::asio::write(*sock,boost::asio::buffer("ok",2)); 发送ok请求
        }
    }
}