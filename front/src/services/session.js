import axios from 'axios'

axios.get("http://localhost:3000/api", { crossdomain: true })

const session = axios.create ({
	baseURL:'http://localhost:3000/api',
	headers: {
		'Accept': 'application/json',
		'Content-Type': 'application/json',
		'Access-Control-Allow-Origin': '*',
		'Access-Control-Allow-Headers': 'Origin, X-Requested-With, Content-Type, Accept',
		'Access-Control-Allow-Methods': 'DELETE, POST, GET, OPTIONS'
	},
	proxy: {
		host: 'https://localhost:3000/api'
	}
})
session.interceptors.response.use((response) => {
	console.log('Response was received')

	return response
 }, (error) => {
	if (error.response.status === 401) {
		return null
	}
	
	return Promise.reject(error)
 })

 export default session
