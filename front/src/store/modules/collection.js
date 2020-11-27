import collectionService from '@/services/collection'

import {
	GET_COLLECTIONS,
	GET_WORDS,
	GET_RESULTS
} from './types'

const initialState = {
	collection: {
		id: '',
		name: '',
		totalWords: 0,
		vocabularyCount: 0,
	},
	collections: [],
	words: [],
	search_results: []
}

const getters = {
	getCollection: state => state.collection,
	getCollections: state => state.collections,
	getWords: state => state.words,
	getResults: state => state.results
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
	},
	getWords ({ commit }) {
		return collectionService.getWords()
		.then(({ data }) => {
			commit(GET_WORDS, data)
		}) 
		.catch(error => {
			throw error
		})
	},
	getResults ({ commit }, { search_words }) {
		console.log("ah? " + search_words)
		return collectionService.searchDocs(search_words)
		.then(({ data }) => {
			commit(GET_RESULTS, data)
		})
		.catch(error => {
			throw error
		})
	}
}

const mutations = {
	[GET_COLLECTIONS] (state, data) {
		state.collections = data
	},
	[GET_WORDS] (state, data) {
		state.words = data
	},
	[GET_RESULTS] (state, data) {
		state.results = data
	}
}

export default {
	namespaced: true,
	state: initialState, getters, actions, mutations
}
