@Grab('log4j:log4j:1.2.17')
@Grab('org.codehaus.groovy.modules.http-builder:http-builder:0.7.1')
import org.apache.log4j.Logger
import org.apache.log4j.Level 
import groovyx.net.http.HTTPBuilder
import static groovyx.net.http.Method.* 
import static groovyx.net.http.ContentType.*
Logger logger = Logger.getLogger("com.foo");
println 'Hello World!'
logger.setLevel(Level.INFO)
logger.error('debug')

//def http = new HTTPBuilder('http://www.baidu.com')  
//def html = http.get(path:'/',query:[q:'groovy'])  
//println html.HEAD 
//println html.BODY

//def http2 = new HTTPBuilder('http://mpstest.abusi.net:6583/mps2')  
//def postBody = [name:'berdy']  
//http2.post(path:'/mgr',body:postBody,requestContentType:URLENC){resp->  
    //assert resp.statusLine.statusCode == 200  
//}


def http = new HTTPBuilder('http://www.baidu.com')  
http.request(GET,TEXT) {  
    //设置url相关信息  
    uri.path='/'  
    uri.query=[a:'1',b:2]  
    //设置请求头信息  
    headers.'User-Agent' = 'Mozill/5.0'  
    //设置成功响应的处理闭包  
    response.success= {resp,reader->  
        println resp.status  
        println resp.statusLine.statusCode  
        println resp.headers.'content-length'  
        println resp.headers  
        //System.out << reader  
    }  
    //根据响应状态码分别指定处理闭包  
    response.'404' = { println 'not found' }  
    //未根据响应码指定的失败处理闭包  
    response.failure = { println "Unexpected failure: ${resp.statusLine}" }  
}
