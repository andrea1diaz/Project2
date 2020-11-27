import session from './session'

const collectionService = {
	getCollections () {
		return session.get('/collection/list')
	},
	getWords () {
		return session.get('/collection/words')
	},
	searchDocs (search_words) {
		console.log(search_words)
		return session.get('/find/hood' )
	}
}

export default collectionService
