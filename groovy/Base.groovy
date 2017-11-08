import groovy.json.JsonBuilder
import groovy.json.JsonSlurper
import groovyx.net.http.HTTPBuilder
import groovyx.net.http.ContentType
import groovyx.net.http.Method
import groovyx.net.http.RESTClient
import groovyx.net.http.HttpResponseDecorator
def test(){
	def x = 1..10
	println x
	[1, 2, 3].each {entry -> println entry}
	Process p="ls -l .".execute()  
	println "${p.text}"
}
def test_type(){
	def a = 1;
	println " ${a} ${a.class}"
	def m = [1: "a", 2: "b"]
	println "${m} ${m.class} ${m[1]}"
}
def test_json(){
	def jsonSlurper = new JsonSlurper()
	def object = jsonSlurper.parseText('{ "name": "John Doe" } /* some comment */')

	assert object instanceof Map
	assert object.name == 'John Doe'
	println "${object} ${object.class} ${object['name']}"
}
def test_xml(){
	def text = '''
		<list>
			<technology>
				<name>Groovy</name>
			</technology>
		</list>
	'''

	def list = new XmlSlurper().parseText(text) 

	assert list instanceof groovy.util.slurpersupport.GPathResult 
	assert list.technology.name == 'Groovy'
	println "${list} ${list.class} ${list['technology']}"
}
def test_file(){
	println new File("/etc/passwd").text 
	def dir = new File(".")  
	if (dir.isDirectory()) {  
		dir.eachFileRecurse { file ->  
			println file  
		}  
	} 
	new File("test.txt").withPrintWriter { printWriter ->  
    	printWriter.println('The first content of file')  
    	printWriter.println('The second content of file')  
    	printWriter.println('The third content of file')  
	} 
	println new File("test.txt").text 
}
def test_closure(){
	log = ''
	(1..10).each{ counter -> log += counter}
	assert log == '1234567891' // assert 失败才会打印
	log = ''
	(1..10).each{log += it}
	assert log == '12345678910' 
	
}
def test_http(){
	def http = new HTTPBuilder('http://www.google.com.hk')  
	http.request(GET, TEXT) {  
	    uri.path="/search"  
	    uri.query = [q:'groovy']  
	  
	  
	    response.success ={resp,reader->  
		println resp.statusLine.statusCode  
		println resp.headers.'content-length'  
		System.out << reader  
	    }  
	    response.failure={resp-> println resp.status }  
	} 	
}
test_http()
