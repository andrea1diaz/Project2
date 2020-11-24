import collectionService from '@/services/collection'

import {
	GET_COLLECTIONS
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
		return collectionService.getCollections()
		.then(({ data }) => {
			commit(GET_COLLECTIONS, data)
		}) 
		.catch(error => {
			throw error
		})
	}
}

const mutations = {
	[GET_COLLECTIONS] (state, data) {
		state.collections = data
	}
}

export default {
	namespaced: true,
	state: initialState, getters, actions, mutations
}
