import session from './session'

const collectionService = {
	getCollections () {
		return session.get('/collection/list')
	}
}

export default collectionService
