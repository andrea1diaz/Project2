import axios from 'axios'

const session = axios.create ({
	baseURL: process.env.VUE_APP_API_URL,
	headers: {
		'Accept': 'application/json',
		'Content-Type': 'application/json'
	}
})

session.interceptors.response.use((response) => {
 	// do something with the response data
 	console.log('Response was received')

 	return response
 }, (error) => {
 	if (error.response.status === 401) {
 		return null
 	}

 	return Promise.reject(error)
 })

 export default session
