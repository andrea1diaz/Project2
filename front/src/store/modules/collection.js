import collectionService from '@/services/collection'

import {
	GET_COLLECTIONS_BEGIN,
	GET_COLLECTIONS_CLEAR,
	GET_COLLECTIONS_FAILURE,
	GET_COLLECTIONS_SUCCESS
} from './types'

const initialState = {
	collection: {
		id: '',
		name: '',
		totalWords: 0,
		vocabularyCount: 0,
	},
	collections: [],
}

const getters = {
	getCollection: state => state.collection,
	getCollections: state => state.collections,
}

const actions = {
	getCollections ({ commit }) {
		commit(GET_COLLECTIONS_BEGIN)
		return collectionService.getCollections()
		.then({ data }) => {
			commit(GET_COLLECTIONS_SUCCESS)
			commit(GET_COLLECTIONS, data)
			return data
		}, 
		.catch(error => {
			commit(GET_COLLECTIONS_FAILURE)
			console.log(error)
		})
	}
}

const mutations = {
	[GET_COLLECTIONS] (state, data) {
		state.collections = data
	}
}
