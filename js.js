	function object2params(object){
		var str = '';
		for(var pro in object){
			if(!object.hasOwnProperty(pro)){
				continue;
			}

			if(object[pro] instanceof Array){
				for(var index in object[pro]){
				    if(!object[pro].hasOwnProperty(index)){
						continue;
					}
					str += pro + '=' + object[pro][index] + '&'; 
				}
			}else{
				str += pro + '=' + object[pro] + '&'; 
			}
		}
		if( str.length > 0 && str[str.length - 1] == '&'){
			str = str.substring(0, str.length - 1);
		}
		return str;
	}
