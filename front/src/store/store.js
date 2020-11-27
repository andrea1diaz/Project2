import Vue from 'vue'
import Vuex from 'vuex'

import collection from '@/store/modules/collection'

Vue.use(Vuex)

const store = new Vuex.Store({
	modules: {
		collection,
	}
})

export default store
