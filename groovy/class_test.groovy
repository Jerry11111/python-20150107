class PretendFieldCounter {
	public count = 0
	//Object get (String name) {
	//	return 'pretend value'
	//}
	//void set (String name, Object value) {
	//	count++
	//}
}
def pretender = new PretendFieldCounter()
println pretender.isNoField
println pretender.count
println pretender.isNoFieldEither
println pretender.count
