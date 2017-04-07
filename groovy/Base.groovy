import groovy.json.JsonBuilder
import groovy.json.JsonSlurper
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
test_file()
